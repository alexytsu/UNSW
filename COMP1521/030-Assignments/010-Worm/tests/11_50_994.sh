~cs1521/bin/spim -file worm.s 11 50 994 | sed -e 's/^.*Iteration/Iteration/;s/ *$//;/Loaded:/d'
