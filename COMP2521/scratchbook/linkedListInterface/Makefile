CC=gcc
FLAGS= -Wall -Werror

interface : LList.o useLists.o listFunctions.o
	$(CC) -o interface LList.o useLists.o listFunctions.o

LList.o : LList.c

useLists.o: useLists.c

listFunctions.o: listFunctions.c

clean :
	rm -f *o interface
