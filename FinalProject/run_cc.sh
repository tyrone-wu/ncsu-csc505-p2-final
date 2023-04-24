#!/bin/bash

function error_exit() {
    echo "error: $1"
    echo 
    echo "usage:   ./run_cc.sh [bfs-s|bfs-p|lp] [directory]"
    echo
    echo "Performs a benchmark using the specified connected components algorithm on the directory of gph files"
    echo 
    echo "arguments:"
    echo "  [bfs-s|bfs-p|lp]    MST algorithm to use"
    echo "    - bfs-s               Sequential BFS"
    echo "    - bfs-p               Parallel BFS"
    echo "    - lp                  Parallel Label Propagation"
    echo "  directory           The directory of where the .gph files are located."
    echo 
    echo "example: ./run_cc.sh ./data/test/t1/input/ "
    exit 1
}

# Error checking
if [ -z "$1" ]
then
    error_exit "First arg is empty."
elif [ "$1" != "bfs-s" ] && [ "$1" != "bfs-p" ] && [ "$1" != "lp" ]
then
    error_exit "Invalid first arg: $1"
elif [ ! -e "./bin/$1" ]
then
    # error_exit "executable file ./bin/$1 does not exist."
    echo "Generating the executable file: $1"
    make "$1"
fi

# Execute CC program
./bin/"$1" "$2"
