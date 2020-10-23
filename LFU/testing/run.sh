#!/bin/bash
FILE1=$1    #input
FILE2=$2    #output
FILE3=$3    #true results
cd ../
make clean
make
cd testing
./../lfu_cache < $FILE1 > $FILE2 
if cmp -s "$FILE2" "$FILE3"; then
    printf '\nResults matched\n'
else
    printf '\nResults did not match\n'
fi