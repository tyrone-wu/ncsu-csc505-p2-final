#!/bin/bash

# Test directory
TEST_DIR=./data/test

# t1 params
T1_N=( 5 10 )
T1_E=( 4 45 )
# Generate t1
mkdir -p $TEST_DIR/t1/input
for i in "${!T1_N[@]}"
do
    ./data/generate/generate.sh rn "${T1_N[$i]}" "${T1_E[$i]}" 1 $TEST_DIR/t1/input 1
done
touch $TEST_DIR/t1/expected.out
echo "${#T1_N[@]}" > $TEST_DIR/t1/expected.out

# t2 params
T2_N=( 10000 100000 100000 )
T2_E=( 49995000 1000000 10000000 )
# Generate t2
mkdir -p $TEST_DIR/t2/input
for i in "${!T2_N[@]}"
do
    ./data/generate/generate.sh rn "${T2_N[$i]}" "${T2_E[$i]}" 1 $TEST_DIR/t2/input 1
done
touch $TEST_DIR/t2/expected.out
echo "${#T2_N[@]}" > $TEST_DIR/t2/expected.out

# Generate t3
mkdir -p $TEST_DIR/t3/input
touch $TEST_DIR/t3/input/v_10.gph
echo "g 10 0" > $TEST_DIR/t3/input/v_10.gph
for (( i = 1; i <= 10; i++ ))
do
    echo "n $i" >> $TEST_DIR/t3/input/v_10.gph
done
touch $TEST_DIR/t3/expected.out
echo "10" > $TEST_DIR/t3/expected.out
