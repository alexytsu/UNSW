~cs1521/bin/spim -file worm.s 5 50 12 | sed -e 's/^.*Iteration/Iteration/;s/ *$//;/Loaded:/d'
