echo "Generating Test Data"
for num in 10000 20000 50000 70000 100000 200000
do
    for type in A D R
    do
        for seed in 1000
        do
            ./gen $num $type $seed > $num_$type_$seed
            echo "============================================================"
            #printf "sortA\t %10d %5c %10d\t" $num $type $seed
            #/usr/bin/time --format="%U seconds" ./sortA < $num_$type_$seed > /dev/null
            printf "sortB\t %10d %5c %10d\t" $num $type $seed
            /usr/bin/time --format="%U seconds" ./sortB < $num_$type_$seed > /dev/null
            #printf "unix\t %10d %5c %10d\t" $num $type $seed
            #/usr/bin/time --format="%U seconds" sort -n < $num_$type_$seed > /dev/null
        done
    done
done

