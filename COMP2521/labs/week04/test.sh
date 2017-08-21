echo "Generating Test Data"
for NUM in 10000 20000 50000 70000 100000 200000
do
    for TYPE in A D R
    do
            ./gen $NUM $TYPE > "$NUM_$TYPE"
            echo "============================================================"
            printf "sortA\t %10d %5c %10d\n" $num $type
            /usr/bin/time --format="%U seconds" ./sortA < $NUM_$TYPE > /dev/null
            printf "sortB\t %10d %5c\n" $num $type
            /usr/bin/time --format="%U seconds" ./sortB < $NUM_$TYPE > /dev/null
            printf "unix\t %10d %5c \n" $num $type
            /usr/bin/time --format="%U seconds" sort -n < $num_$TYPE > /dev/null
    done
done

