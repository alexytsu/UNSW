CC=gcc
CFLAGS=-Wall -lm -std=c11 -g
HELPER=getLinks.c graph.c frequency.c linkedList.c neatening.c newTree.c set.c ratioList.c perms.c setRank.c
all: pagerank inverted searchTfIdf searchPagerank bruteforce
pagerank: $(HELPER) pagerank.c
	$(CC) $(CFLAGS) pagerank.c $(HELPER) -o pagerank
inverted: $(HELPER) inverted.c
	$(CC) $(CFLAGS) inverted.c $(HELPER) -o inverted
searchTfIdf: $(HELPER) searchTfIdf.c
	$(CC) $(CFLAGS) searchTfIdf.c $(HELPER) -o searchTfIdf
searchPagerank: $(HELPER) searchPagerank.c
	$(CC) $(CFLAGS) searchPagerank.c $(HELPER) -o searchPagerank
bruteforce: $(HELPER) bruteforce.c 
	$(CC) $(CFLAGS) bruteforce.c $(HELPER) -o bruteforce
clean:
	rm searchPagerank inverted searchTfIdf pagerank bruteforce
