#!/bin/bash
CMD=$1

cd ../source/
pwd

if [ "$CMD" = "compile" ]; then

    printf 'Compiling project...\n\n'

    make clean
    make

fi

if [ "$CMD" = "clean" ]; then

    printf 'Cleaning...\n\n'

    make clean

fi

if [ "$CMD" = "rf" ]; then

    FILE1=$2    #input
    FILE2=$3    #output
    FILE3=$4    #true results
    
    
    FULL_NAME1="../tests/$FILE1"
    FULL_NAME2="../tests/$FILE2"
    FULL_NAME3="../tests/$FILE3"

    printf '\n\nRunning program... \n\n'

    ./main < $FULL_NAME1 > $FULL_NAME2 

    if cmp -s "$FULL_NAME2" "$FULL_NAME3"; then
        printf '\nResults matched\n'
    else
        printf '\nResults did not match\n'
    fi

fi

if [ "$CMD" = "rs" ]; then

    FILE1=$2    #input

    FULL_NAME1="../tests/$FILE1"  

    printf '\n\nRunning program... \n\n'
   
    ./main < $FULL_NAME1 

fi


if [ "$CMD" = "gt" ]; then

    printf '\n\nRunning program... \n\n'
   
    ./main_gtest

fi