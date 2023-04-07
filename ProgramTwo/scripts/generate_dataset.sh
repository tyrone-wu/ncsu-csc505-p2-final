#!/bin/bash

# Data generate script
GEN_CMD="./data/generate/generate.sh rn" 
# Where to write dataset to
DATA_DIR=./data/experiment/input

# Seeds of dataset
SEEDS=( 1 2 3 4 5 )

# Starting number of vertices
S_V=1000
# Ending number of vertices
E_V=10000

# Iterate number of vertices
for (( V = $S_V; V <= $E_V; V *= 10 ))
do
    # Increment edges 10 times from 3 * vertices to max
    e_start=$(( 3 * $V ))
    e_end=$(( ($V * ($V - 1)) / 2 ))

    increment=$(( ($e_end - $e_start) / 10 ))

    # Iterate number of edges
    for (( E = $e_start; E <= $e_end; E += increment ))
    do
        # Create dir if not exist
        mkdir -p $DATA_DIR/V-$V/E-$E

        # Iterate seeds
        for seed in "${SEEDS[@]}"
        do
            $GEN_CMD $V $E $seed $DATA_DIR/V-$V/E-$E $V
        done
    done
    echo
done

echo "Finished generating dataset."
