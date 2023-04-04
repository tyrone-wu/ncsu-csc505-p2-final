# Program Two for (team name)

## Teammates

* Andrew Sauerbrei, amsauerb
* AJ Bulthuis, ajbulthu
* Tyrone Wu, tkwu

## Usage

### Compiling the program

```sh
# example: make prim
$ make [prim|kruskal]

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
```sh
# Execute script
# example: `./run_mst.sh prim < ./data/input_01.gph`
$ ./run_mst.sh [prim|kruskal] < [file_path]

# output:
# g 5 5
# e 1 2 1
# ...
# weight      WEIGHT_OF_MST
# runtime     SECONDS
# comparisons NUMBER_OF_COMPARISONS
```

For edges of the MST: 
```sh
# MST is printed onto standard output
$ ./run_mst.sh prim < ./data/input_01.gph 2> /dev/null

# output:
# g 5 5
# e 1 2 1
# ...
# e 1 5 1
```

Format of standard output:
```sh
# Format:
g number_of_nodes number_of_edges
e source_1 target_1 weight_1
...
e source_m target_m weight_m
```

For benchmark only:
```sh
# Benchmark is printed onto standard error
$ ./run_mst.sh prim < ./data/input_01.gph 1> /dev/null

# output:
# weight      WEIGHT_OF_MST
# runtime     SECONDS
# comparisons NUMBER_OF_COMPARISONS
```

### Run test cases

```sh
# example: make test-prim
$ make [test-prim|test-kruskal]

# output:
# ...
# 🧪 Running prim MST with c5.gph:
# Test case c5.gph passed. ✅ :)

# 🧪 Running prim MST with bt7.gph:
# Test case bt7.gph passed. ✅ :)
```
