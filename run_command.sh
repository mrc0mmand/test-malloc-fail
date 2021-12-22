#!/bin/bash

set -u
set -o pipefail

ulimit -c 0

MALLOC_MIN=0
MALLOC_MAX=1000

for ((i = MALLOC_MIN; i < MALLOC_MAX; i++)); do
   LD_PRELOAD=build/libtest_malloc_fail.so MALLOC_FAIL_AT=$i "$@" 
   if [[ $? -eq 139 ]]; then
       echo "Command '$*' failed with MALLOC_FAIL_AT=$i"
       exit 1
   fi
done
