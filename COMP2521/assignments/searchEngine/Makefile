CC=gcc
CFLAGS=-Wall -lm -std=c11
HELPER=getLinks.c graph.c frequency.c linkedList.c neatening.c newTree.c set.c
all: pagerank inverted searchTfIdf searchPagerank
pagerank: $(HELPER) pagerank.c
	$(CC) $(CFLAGS) pagerank.c $(HELPER) -o pagerank
inverted: $(OBJS) inverted.c
	$(CC) $(CFLAGS) inverted.c $(HELPER) -o inverted
searchTfIdf: $(OBJS) searchTfIdf.c
	$(CC) $(CFLAGS) searchTfIdf.c $(HELPER) -o searchTfIdf
searchPagerank: $(OBJS) searchPagerank.c
	$(CC) $(CFLAGS) searchPagerank.c $(HELPER) -o searchPagerank
clean:
	rm searchPagerank inverted searchTfIdf pagerank *.txt
