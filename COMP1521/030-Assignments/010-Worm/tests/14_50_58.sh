~cs1521/bin/spim -file worm.s 14 50 58 | sed -e 's/^.*Iteration/Iteration/;s/ *$//;/Loaded:/d'
