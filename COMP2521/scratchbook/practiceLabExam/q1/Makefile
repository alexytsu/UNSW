# COMP2521 17s2; Question: removeValue

CC=gcc
CFLAGS=-Wall -Werror

all: testRemoveValue

testRemoveValue : DLList.o  removeValue.o testRemoveValue.o
	$(CC) -o testRemoveValue  DLList.o  removeValue.o testRemoveValue.o

removeValue.o : removeValue.c removeValue.h DLList.h 

testRemoveValue.o : testRemoveValue.c removeValue.h DLList.h 

clean:
	rm -f testRemoveValue removeValue.o testRemoveValue.o core
