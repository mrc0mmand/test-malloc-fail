#!/bin/bash

set -u
set -o pipefail

ulimit -c 0

MALLOC_MIN=0
MALLOC_MAX=1000
MALLOC_STEP=1

while getopts "l:h:s:" opt; do
    case "$opt" in
        l)
            MALLOC_MIN="$OPTARG"
            ;;
        h)
            MALLOC_MAX="$OPTARG"
            ;;
        s)
            MALLOC_STEP="$OPTARG"
            ;;
        *)
            echo >&2 "Usage: $0 [-l MALLOC_MIN] [-h MALLOC_HIGH] [-s MALLOC_STEP]"
            exit 1
    esac
done

shift $((OPTIND - 1))

for ((i = MALLOC_MIN; i < MALLOC_MAX; i += MALLOC_STEP)); do
   LD_PRELOAD=build/libtest_malloc_fail.so MALLOC_FAIL_AT=$i "$@" 
   if [[ $? -eq 139 ]]; then
       echo "Command '$*' failed with MALLOC_FAIL_AT=$i"
       exit 1
   fi
done
