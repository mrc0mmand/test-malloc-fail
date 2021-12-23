#!/bin/bash

set -u
set -o pipefail

ulimit -c 0

# TODO: logging & continue after segv

ALLOC_MIN=0
ALLOC_MAX=1000
ALLOC_STEP=1
ALLOC_FUN=malloc

while getopts "f:h:l:s:" opt; do
    case "$opt" in
        f)
            ALLOC_FUN="$OPTARG"
            ;;
        h)
            ALLOC_MAX="$OPTARG"
            ;;
        l)
            ALLOC_MIN="$OPTARG"
            ;;
        s)
            ALLOC_STEP="$OPTARG"
            ;;
        *)
            echo >&2 "Usage: $0 [-l ALLOC_MIN] [-h ALLOC_MAX] [-s ALLOC_STEP]"
            exit 1
    esac
done

shift $((OPTIND - 1))

ALLOC_FAIL_AT="${ALLOC_FUN^^}_FAIL_AT"

for ((i = ALLOC_MIN; i < ALLOC_MAX; i += ALLOC_STEP)); do
    declare -x "$ALLOC_FAIL_AT=$i"
    # TODO: don't harcode the build directory
    LD_PRELOAD="$PWD/build/libtest_malloc_fail.so" "$@"
    if [[ $? -eq 139 ]]; then
        echo "Command '$*' failed with $ALLOC_FAIL_AT=$i"
        echo "Reproducer: $ALLOC_FAIL_AT=$i LD_PRELOAD=$PWD/build/libtest_malloc_fail.so $*"
        exit 1
    fi
done
