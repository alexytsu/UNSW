echo "Generating C solutions"

rm -rf tests/
mkdir tests

for length in 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19
do
    for iterations in 50
    do
        for seed in 123 3456 9999 12 994 43 58
        do
            echo "Generating .exp ${length} ${iterations} ${seed}"
            ./worm $length $iterations $seed | sed -e 's/^.*Iteration/Iteration/;s/ *$//;/Loaded:/d'> tests/"${length}_${iterations}_${seed}.exp"
            echo "Generating .sh"
            echo "~cs1521/bin/spim -file worm.s ${length} ${iterations} ${seed} | sed -e 's/^.*Iteration/Iteration/;s/ *$//;/Loaded:/d'" > tests/"${length}_${iterations}_${seed}.sh"

        done
    done
done

echo "Generating test scripts"


