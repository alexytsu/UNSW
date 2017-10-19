all: invertedIndex pagerank tfidf
invertedIndex: getLinks.c graph.c linkedList.c set.c invertedIndex.c neatening.c
	gcc -g -std=c11 getLinks.c  graph.c linkedList.c set.c invertedIndex.c neatening.c -o invertedIndex
pagerank: getLinks.c graph.c pagerank.c
	gcc -g -std=c11 getLinks.c graph.c pagerank.c -o pagerank
tfidf: bstree.c frequency.c getLinks.c bstree.c neatening.c searchTfIdf.c
    gcc -g -std=c11 bstree.c frequency.c getLinks.c bstree.c neatening.c searchTfIdf.c -o tfidf
clean:
	rm pagerank invertedIndex bstree
