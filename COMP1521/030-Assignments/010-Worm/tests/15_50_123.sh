~cs1521/bin/spim -file worm.s 15 50 123 | sed -e 's/^.*Iteration/Iteration/;s/ *$//;/Loaded:/d'
