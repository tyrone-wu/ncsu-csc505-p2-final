#!/bin/bash

IN_DIR=./data/experiment/input-01
OUT_DIR=./data/experiment/results/e

# Threads to test
THREADS=( 1 2 4 12 )

# Benchmark algo on v and e size; $1 = algo, $2 = k
function benchmark() {

    # Iterate v-size dirs
    v_directories=( "$IN_DIR"/* )
    v_directories=( $(
        for v_dir in "${v_directories[@]}"
        do
            basename "$v_dir"
        done | sort -t - -k 2 -g
    ) )
    for v_dir in "${v_directories[@]}"
    do

        # Iterate c-components dirs
        c_directories=( "$IN_DIR"/"$v_dir"/* )
        c_directories=( $(
            for c_dir in "${c_directories[@]}"
            do
                basename "$c_dir"
            done | sort -t - -k 2 -g
        ) )
        for c_dir in "${c_directories[@]}"
        do

            # Iterate threads
            for t in "${THREADS[@]}"
            do
                # Create dir and file
                write_dir=$OUT_DIR/"$v_dir"/"$c_dir"/"$1"
                mkdir -p "$write_dir"

                write_file=$write_dir/"$1"_t-"$t".csv
                touch "$write_file"
                echo "edges,b1,b2,b3,b4" > "$write_file"

                # Iterate e-size dirs
                e_directories=( "$IN_DIR"/"$v_dir"/"$c_dir"/* )
                e_directories=( $(
                    for e_dir in "${e_directories[@]}"
                    do
                        basename "$e_dir"
                    done | sort -t - -k 2 -g
                ) )
                for e_dir in "${e_directories[@]}"
                do

                    # Append new row
                    e_size=${e_dir#*-}
                    echo -n "$e_size" >> "$write_file"

                    # Iterate seeds/batches
                    b_directories=( "$IN_DIR"/"$v_dir"/"$c_dir"/"$e_dir"/* )
                    b_directories=( $(
                        for b_dir in "${b_directories[@]}"
                        do
                            basename "$b_dir"
                        done | sort -t - -k 2 -g
                    ) )
                    for b_dir in "${b_directories[@]}"
                    do

                        # Read directory
                        read_dir=$IN_DIR/$v_dir/$c_dir/$e_dir/$b_dir

                        echo "Running $1 t=$t on $read_dir"
                        result=$(./bin/"$1" "$read_dir" "$t" 2>&1 > /dev/null)
                        result=( $result )

                        echo -n ",${result[6]}" >> "$write_file"
                    done

                    echo "" >> "$write_file"
                done
            done

        done
    done
}

# Parallel bfs
echo "Benchmarking Parallel LP"
benchmark lp
