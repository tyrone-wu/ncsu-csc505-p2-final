#!/bin/bash

IN_DIR=./data/experiment/input-02
# Where to write the results to
OUT_DIR=./data/experiment/results/e
# k-values for prim's
K_s=( 1 2 3 4 5 6 )

# Benchmark algo on v and e size; $1 = algo, $2 = k
function benchmark() {
    # Iterate V-size dirs
    v_directories=( $IN_DIR/* )
    v_directories=( $(
        for v_dir in "${v_directories[@]}"
        do
            basename $v_dir
        done | sort -t - -k 2 -g
    ) )
    for v_dir in "${v_directories[@]}"
    do
        # Create dir and file
        write_dir=$OUT_DIR/$v_dir
        mkdir -p $write_dir

        write_file_rt=$write_dir/"$1"-k"$2"-runtimes.csv
        write_file_cmp=$write_dir/"$1"-k"$2"-compares.csv

        touch $write_file_rt
        echo "edges,s1,s2,s3,s4,s5" > $write_file_rt
        touch $write_file_cmp
        echo "edges,s1,s2,s3,s4,s5" > $write_file_cmp

        # Iterate E-size dirs
        e_directories=( $IN_DIR/$v_dir/* )
        e_directories=( $(
            for e_dir in "${e_directories[@]}"
            do
                basename $e_dir
            done | sort -t - -k 2 -g
        ) )
        for e_dir in "${e_directories[@]}"
        do
            # Append new row
            e_size=${e_dir#*-}
            echo -n "$e_size" >> $write_file_rt
            echo -n "$e_size" >> $write_file_cmp

            # Read directory
            read_dir=$IN_DIR/$v_dir/$e_dir

            # Iterate seeds
            seed_files=( $read_dir/* )
            for data in "${seed_files[@]}"
            do
                echo "Running $1 k=$2 on $data"
                result=$(./bin/"$1" "$2" < $data 2>&1 > /dev/null)
                result=( $result )

                echo -n ",${result[3]}" >> $write_file_rt
                echo -n ",${result[5]}" >> $write_file_cmp
            done
            
            echo "" >> $write_file_rt
            echo "" >> $write_file_cmp
        done
    done

    echo
}

# Kruskal's
echo "Benchmarking Kruskal's"
benchmark kruskal 1

# Prim's
for k in "${K_s[@]}"
do
    echo "Benchmarking Prim's k = $k"
    benchmark prim $k
done

# Prim's lazy
echo "Benchmarking Lazy Prim's"
benchmark primLazy 1
