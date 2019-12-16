~cs1521/bin/spim -file worm.s 6 50 3456 | sed -e 's/^.*Iteration/Iteration/;s/ *$//;/Loaded:/d'
