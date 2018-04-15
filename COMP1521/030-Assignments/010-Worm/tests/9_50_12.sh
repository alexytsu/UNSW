~cs1521/bin/spim -file worm.s 9 50 12 | sed -e 's/^.*Iteration/Iteration/;s/ *$//;/Loaded:/d'
