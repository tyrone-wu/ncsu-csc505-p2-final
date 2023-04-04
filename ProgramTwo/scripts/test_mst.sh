#!/bin/bash

TEST_DIR=./data/test
DATA_DIR=./data/ProgramTwo-Student-Files
DATA=( c5 bt7 )

if [ ! -e "./bin/$1" ]
then
    make "$1"
fi

for input in "${DATA[@]}"
do
    mkdir -p $TEST_DIR

    echo
    echo "🧪 Running $1 MST with $input.gph:"

    ./bin/"$1" < $DATA_DIR/"$input".gph 1> $TEST_DIR/"$input"-actual.out 2> $TEST_DIR/"$input"-actual.err

    sort $TEST_DIR/"$input"-actual.out | grep "^[ge]" > $TEST_DIR/"$input"-actual.txt
    sort $DATA_DIR/"$input".out | grep "^[ge]" > $TEST_DIR/"$input"-expected.txt

    if ! diff -q --strip-trailing-cr $TEST_DIR/"$input"-actual.txt $TEST_DIR/"$input"-expected.txt &> /dev/null
    then
        echo "Test case $input.gph failed. ❌ :("
        exit 1
    fi

    echo "Test case $input.gph passed. ✅ :)"
done
