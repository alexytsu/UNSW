#!/bin/sh

for t in 01 02 03 04 05 06 07
do
    echo === Test $t ===
    sort -n < tests/$t > tests/$t.expected
    ./usel < tests/$t > tests/$t.observed
    diff tests/$t.expected tests/$t.observed
done
rm tests/*.expected tests/*.observed
