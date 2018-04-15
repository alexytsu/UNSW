~cs1521/bin/spim -file worm.s 18 50 12 | sed -e 's/^.*Iteration/Iteration/;s/ *$//;/Loaded:/d'
