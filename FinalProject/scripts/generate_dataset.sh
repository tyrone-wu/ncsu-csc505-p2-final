#!/bin/bash

# Data generate script
GEN_CMD="./data/generate/generate.sh rn" 
# Where to write dataset to
DATA_DIR=./data/experiment/input

# Components
COMPONENTS=( 1 3 6 )
# Vertices
# VERTICES=( 1020 10200 102000 )
VERTICES=( 102000 )
# Number of batches
BATCHES=4

# Max edges that can be generated from the script, 800,000,000
capacity=200000000

# Iterate number of vertices
for total_v in "${VERTICES[@]}"
do
    echo "total vertices $total_v"

    for comps in "${COMPONENTS[@]}"
    do 
        v=$(( total_v / comps ))
        echo "components $comps"

        # Edges
        EDGES=()

        min=$(( v - 1 ))
        # max=$(( v * (v - 1) / 10 ))
        # max=$(( max > capacity ? capacity : max ))

        # Calculate edges for each vertex size
        # Minimum
        EDGES+=( $min )
        # Sparse
        EDGES+=( $(( v * 3 )) )
        EDGES+=( $(( v * 9 )) )
        # Medium
        EDGES+=( $(( v * 27 )) )
        EDGES+=( $(( v * 81 )) )
        # Dense
        EDGES+=( $(( v * 243 )) )
        EDGES+=( $(( v * 729 )) )
        # Dense
        # EDGES+=( $max )

        # Iterate edges
        for e in "${EDGES[@]}"
        do
            echo "edges $e"

            # Iterating components to generate
            for (( c = 0; c < comps; c++ ))
            do
                for (( b = 1; b <= BATCHES; b++ ))
                do
                    mkdir -p $DATA_DIR/v-"$total_v"/c-"$comps"/e-"$e"/b-"$b"

                    # Gen data
                    seed=$(( c * BATCHES + b ))
                    $GEN_CMD $v "$e" $seed $DATA_DIR/v-"$total_v"/c-"$comps"/e-"$e"/b-"$b" 1

                    # echo "$GEN_CMD $v $e $seed $DATA_DIR/v-$total_v/c-$comps/e-$e/b-$b 1"
                    # touch $DATA_DIR/v-"$total_v"/c-"$comps"/e-"$e"/b-"$b"/s-$seed.txt
                done
            done
        done

        echo 
    done
done

echo "Finished generating dataset."
