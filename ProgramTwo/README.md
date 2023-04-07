# Program Two for DEF

## Teammates

* Andrew Sauerbrei, amsauerb
* AJ Bulthuis, ajbulthu
* Tyrone Wu, tkwu

## Usage

### Compiling the program

```sh
# example: make prim
$ make [primLazy|prim|kruskal]

# output: 
# clang++ -std=c++20 -c src/main.cpp -o ./build/main.o
# ...
# clang++ -std=c++20 ./build/main.o ./build/Vertex.o ./build/Graph.o ./build/BinaryHeap.o ./build/Time.o ./build/prim.o -o ./bin/prim
```

### Running the script

Before execution: 
```sh
# May need to convert Windows line ending to Unix
$ sed -i -e 's/\r$//' run_mst.sh

# Make the script executable
$ chmod +x run_mst.sh
```

Script execution:  
Setting `k` to `1` in the D-ary Heap (D = 2^k) is equivalent to a Binary Heap:
```sh
# Execute script
# example: `./run_mst.sh prim 1 < ./data/input_01.gph`
$ ./run_mst.sh [primLazy|prim|kruskal] [k_value] < [file_path]

# arguments:
#   [primLazy|prim|kruskal]     MST algorithm to use
#     - primLazy                    Prim-Jarnik's algorithm with lazy deletion and no decrease key
#     - prim                        Prim-Jarnik's algorithm with decrease key
#     - kruskal                     Kruskal's algorithm with disjoint sets
#   k_value                     Sets the node size for d-ary heap, d = 2^k. Set k = 1 for binary heap.
#   file_path                   File that contains the graph; must be in format .gph
```

Example Usages:
```sh
# Prim's with lazy deletion and binary heap
$ ./run_mst.sh primLazy 1 < [file_path]

# Prim's with decrease key and d-ary heap of d = 2^k
$ ./run_mst.sh prim [k_value] < [file_path]

# Kruskal's with disjoint sets and binary heap
$ ./run_mst.sh kruskal 1 < [file_path]
```
