~cs1521/bin/spim -file worm.s 16 50 9999 | sed -e 's/^.*Iteration/Iteration/;s/ *$//;/Loaded:/d'
