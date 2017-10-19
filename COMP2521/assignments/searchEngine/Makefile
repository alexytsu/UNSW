all: invertedIndex pagerank tfidf searchPagerank
invertedIndex: getLinks.c graph.c linkedList.c set.c invertedIndex.c neatening.c
	gcc -g -std=c11 getLinks.c  graph.c linkedList.c set.c invertedIndex.c neatening.c -o invertedIndex
pagerank: getLinks.c graph.c pagerank.c
	gcc -g -std=c11 getLinks.c graph.c pagerank.c -o pagerank
tfidf: frequency.c getLinks.c newTree.c neatening.c searchTfIdf.c linkedList.c set.c
	gcc -g -lm  -std=c11 frequency.c getLinks.c newTree.c neatening.c searchTfIdf.c set.c linkedList.c -o tfidf
searchPagerank: searchPagerank.c
	gcc -g -std=c11 searchPagerank.c -o searchPagerank
clean:
	rm pagerank invertedIndex bstree
