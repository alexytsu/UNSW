# COMP1521 18s1 Assignment 2

CC = dcc
CFLAGS = -Wall -Werror -std=c99
BINS = test1 test2 test3 myHeap.o

all : $(BINS)

test1 : test1.o myHeap.o
test2 : test2.o myHeap.o
test3 : test3.o myHeap.o
myHeap.o: myHeap.c

clean :
	rm -f $(BINS) *.o core
