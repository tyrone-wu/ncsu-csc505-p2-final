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
E_V=100000

# Iterate number of vertices
for (( V = $S_V; V <= $E_V; V *= 10 ))
do
    # Iterate number of edges
    for (( E = 3 * $V; E <= ($V * ($V - 1)) / 2; E *= 3 ))
    do
        # Break if gets too large
        if [ "$E" -gt 25000000 ] 
        then
            break
        fi

        # Create dir if not exist
        mkdir -p $DATA_DIR/V-$V/E-$E

        # Iterate seeds
        for seed in "${SEEDS[@]}"
        do
            $GEN_CMD $V $E $seed $DATA_DIR/V-$V/E-$E $V
        done
    done
done

echo "Finished generating dataset."
