#!/bin/sh

# Create a directory to hold test cases
rm -rf tests
mkdir tests

# Compile the program
make clean
make

# Create the test cases
echo Generating lists
for num in 10000 25000 50000 100000 110000
do
    seq $num | sort -nr > tests/reversed$num
    seq $num | sort -R > tests/random$num
    seq $num > tests/sorted$num
    ./randl $num > tests/random_dup$num
    ./randl $num | sort -nr > tests/reversed_dup$num
    ./randl $num | sort -n > tests/sorted_dup$num
done
echo Lists Generated

# Run multiple tests for each case
for num in 10000 25000 50000 100000 110000
do
    for style in reversed random sorted random_dup reversed_dup sorted_dup
    do
        for trial in 0 1 2
        do
            echo UNIX_SORT $style $num trial $trial $(time sort -n < tests/$style$num > /dev/null)
            echo INSERT_SORT $style $num trial $trial $(time ./usel < tests/$style$num > /dev/null)
        done
    done
done

# Clean up
make clean
rm -rf tests
