~cs1521/bin/spim -file worm.s 13 50 9999 | sed -e 's/^.*Iteration/Iteration/;s/ *$//;/Loaded:/d'
