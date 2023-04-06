#!/bin/bash

function error_exit() {
    echo "error: $1"
    echo 
    echo "usage:   ./run_mst.sh [prim|kruskal] [k_value] < [file_path]"
    echo
    echo "Performs a benchmark using the specified MST algorithm on an input from STDIN"
    echo 
    echo "arguments:"
    echo "  [prim|kruskal]      MST algorithm to use"
    echo "    - prim                Prim-Jarník's algorithm"
    echo "    - kruskal             Kruskal's algorithm"
    echo "  k_value             Sets the node size for d-ary heap, d = 2^k. Set k = 1 for binary heap."
    echo "  file_path           File that contains the graph; must be in format .gph"
    echo 
    echo "example: ./run_mst.sh prim < ./data/input_01.gph"
    exit 1
}

# Error checking
if [ -z "$1" ]
then
    error_exit "First arg is empty."
elif [ "$1" != "prim" ] && [ "$1" != "kruskal" ]
then
    error_exit "Invalid first arg: $1"
elif [ ! -e "./bin/$1" ]
then
    # error_exit "executable file ./bin/$1 does not exist."
    echo "Generating the executable file: $1"
    make "$1"
fi

# Execute MST program
./bin/"$1" 1
