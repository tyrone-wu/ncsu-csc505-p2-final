#!/bin/bash

# Tst file directory
TEST_DIR=./data/test/"$1"-k"$2"
# Input file directory
DATA_DIR=./data/ProgramTwo-Student-Files
# The datasets to test on
DATA=( bt7 c5 dt_00005_000000_0100_01 dt_100000_000000_100000_01 gm_00010_000020_0500_01 gm_100000_3000000_100000_01 gw_00010_000020_1000_01 gw_100000_3000000_100000_01 p5 rn_00005_000010_0200_01 rn_00010_000020_0500_01 rn_10000_050000_50000_01 rn_20000_100000_50000_01 rn_40000_200000_50000_01 rn_1000000_3000000_100000_01 )

# Compile program if does not exist
if [ ! -e "./bin/$1" ]
then
    make "$1"
fi

# Iterate input datasets
for input in "${DATA[@]}"
do
    # Create dir if not exist
    mkdir -p $TEST_DIR

    echo
    echo "🧪 Running $1 MST with $input.gph:"

    # Run and record algo on input
    ./bin/"$1" "$2" < $DATA_DIR/"$input".gph 1> $TEST_DIR/"$input"-actual.out 2> $TEST_DIR/"$input"-actual.err

    # Filter output for to standardize compare
    sort $TEST_DIR/"$input"-actual.out | grep "^[ge]" > $TEST_DIR/"$input"-actual.txt
    sort $DATA_DIR/"$input".out | grep "^[ge]" > $TEST_DIR/"$input"-expected.txt

    # Check if edges of MST differ between actual and expected
    if ! diff -q --strip-trailing-cr $TEST_DIR/"$input"-actual.txt $TEST_DIR/"$input"-expected.txt &> /dev/null
    then
        echo "Edges of MST are not equal. ❌ "
    else
        echo "Edges of MST are equal. ✅ "
    fi

    # Extract number of compares
    actual_compares=$(awk 'NR==3 {print $2}' $TEST_DIR/"$input"-actual.err)
    expected_compares=$(awk 'NR==3 {print $2}' $DATA_DIR/"$input".err)

    # Extract MST weight
    actual_weight=$(awk 'NR==1 {print $2}' $TEST_DIR/"$input"-actual.err)
    expected_weight=$(awk 'NR==1 {print $2}' $DATA_DIR/"$input".err)

    # Check if MST differ between actual and expected
    echo "Actual MST weight | compares:   $actual_weight 	| $actual_compares"
    echo "Expected MST weight | compares: $expected_weight 	| $expected_compares"
    if [ $actual_weight == $expected_weight ]
    then
        echo "Test case $input.gph passed. ✅ :)"
    else
        echo "Test case $input.gph failed. ❌ :("
    fi
done
