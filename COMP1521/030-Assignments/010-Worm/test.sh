#!/bin/sh

case $# in
0) BIN="-" ;;
1) BIN="$1" ;;
*) echo "Usage: $0 FileName" ; exit 1 ;;
esac

case "$BIN" in
*.c)
	BIN=`basename "$BIN" .c`
	if [ ! -f "Makefile" ]
	then
		echo "No Makefile here. Are you in the right directory?"
		exit 1
	fi
	
	if [ ! -x "$BIN" ]
	then
		echo "No executable file called $BIN. Did you run make?"
		exit 1
	fi
	;;
*.s)
	if [ ! -f "$BIN" ]
	then
		echo "No file called $BIN in this directory"
		exit 1
	fi
	;;
*)
	;;
esac

if [ ! -d tests ]
then
	echo "No tests/ directory here. Are you in the right directory?"
	exit 1
fi

if [ "$BIN" = "-" ]
then
	echo "Running tests ..."
else
	echo "Running tests on $BIN ..."
fi

ulimit -t 5
for tt in tests/*.sh
do
	t=`basename $tt .sh`
	sh "$tt" "$BIN" 2>&1 | head -1000 > tests/$t.out
	if cmp -s tests/$t.exp tests/$t.out
	then
		echo Passed test $t
	else
		echo Failed test $t
#		printf "%-35s%-35s\n\n" "Your Output" "Expected Output" > tests/$t.cmp
#		pr -m -t -w 70 tests/$t.out tests/$t.exp >> tests/$t.cmp
#		echo Check differences using \"cat tests/$t.cmp\"
		echo Check differences using \"diff tests/$t.exp tests/$t.out\"

	fi
done

