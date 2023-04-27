#!/bin/bash

# Test directory
TEST_DIR=./data/test

# The dir datasets to test on
DATA=( t1 t2 t3 )

# Compile program if does not exist
if [ ! -e "./bin/$1" ]
then
    make "$1"
fi

# Iterate input datasets
for dir in "${DATA[@]}"
do
    # Create dir if not exist
    path=$TEST_DIR/"$dir"
    mkdir -p "$path"/"$1"

    echo
    echo "🧪 Running $1 on $dir:"
    # Run and record algo on input
    ./bin/"$1" "$path"/input "$2" 1> "$path"/"$1"/actual.out 2> "$path"/"$1"/actual.err

    # Compare actual and expected
    cat "$path"/"$1"/actual.err
    if cmp --silent -- "$path"/"$1"/actual.out "$path"/expected.out
    then
        echo "Test case passed. ✅ :)"
    else
        echo "Test case failed. ❌ :("
    fi
done
