# Final Project for DEF

## Teammates

* Andrew Sauerbrei, amsauerb
* AJ Bulthuis, ajbulthu
* Tyrone Wu, tkwu

## Usage

### Compiling the program

```sh
# example: make bfs-p
$ make [bfs-p|lp]

# output: 
# clang++ -std=c++20 -c src/main.cpp -o ./build/main.o
# ...
```

### Running the script

Before execution: 
```sh
# May need to convert Windows line ending to Unix
$ sed -i -e 's/\r$//' run_cc.sh

# Make the script executable
$ chmod +x run_cc.sh
```

<!-- Run test cases:  
```sh
# Generate test data; only needs to be done once
$ make gen-test

# Execute test script
# example: `make test-bfs-p`
$ make [test-bfs-p|test-lp]

# output: 
# ...
# Running lp on t2:
# Test case failed. ✅ :)
# ...
``` -->

Script execution:  
```sh
# Execute script
# example: `./run_cc.sh bfs-p ./data/dir-1/ 1`
$ ./run_mst.sh [bfs-p|lp] [directory] [threads]

# arguments:
#   [bfs-p|lp]    CC algorithm to use"
#     - bfs-p       Parallel BFS
#     - lp          Parallel Label Propagation
#   directory     The directory of where the .gph files are located. All .gph files in the directory will be read into the program.
#   threads       Number of threads to utilize
```

<!-- Example Usages:
```sh
# Prim's with lazy deletion and binary heap
$ ./run_mst.sh primLazy 1 < [file_path]

# Prim's with decrease key and d-ary heap of d = 2^k
$ ./run_mst.sh prim [k_value] < [file_path]

# Kruskal's with disjoint sets with rank and binary heap
$ ./run_mst.sh kruskal 1 < [file_path]
``` -->

### Experiment

Generating the dataset:  
Note: Overall, this comes out to 19.0 GB and takes a pretty long time to generate (~3+ hours?)
```sh
# Execute script
$ ./scripts/generate_dataset.sh

# Dataset directory structure
./data/experiment/input/
└── v-102000
    ├── c-1
    |   ├── e-101999
    |   |   └── ...
    |   ├── ...
    |   └── e-74358000
    |       └── ...
    |
    ├── c-3
    |   ├── e-33999
    |   |   └── ...
    |   ├── ...
    |   └── e-24786000
    |       └── ...
    |
    └── c-6
        ├── e-16999
        |   └── ...
        ├── ...
        └── e-12393000
            └── ...
```

Running the experiment:  
Note: Also takes a long time to run (3+ hours)
```sh
# Execute script
$ ./scripts/run_experiment.sh

# Results are located in
./data/experiment/results/e/
└── v-102000
    ├── c-1
    |   ├── bfs-p
    |   |   └── ...
    |   └── lp
    |       └── ...
    |
    ├── c-3
    |   ├── bfs-p
    |   |   └── ...
    |   └── lp
    |       └── ...
    |
    └── c-6
        ├── bfs-p
        |   └── ...
        └── lp
            └── ...
```
