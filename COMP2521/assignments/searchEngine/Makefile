all: invertedIndex pagerank
invertedIndex: getLinks.c graph.c linkedList.c set.c invertedIndex.c neatening.c
	gcc -g -std=c11 getLinks.c  graph.c linkedList.c set.c invertedIndex.c neatening.c -o invertedIndex
pagerank: getLinks.c graph.c pagerank.c
	gcc -g -std=c11 getLinks.c graph.c pagerank.c -o pagerank
clean:
	rm pagerank invertedIndex
