all: invertedIndex pagerank tfidf searchPagerank
invertedIndex: getLinks.c graph.c linkedList.c set.c invertedIndex.c neatening.c
	gcc -Wall -Werror -g getLinks.c  graph.c linkedList.c set.c invertedIndex.c neatening.c -o invertedIndex
pagerank: getLinks.c graph.c pagerank.c
	gcc -Wall -Werror -g -std=c11 getLinks.c graph.c pagerank.c -o pagerank
tfidf: frequency.c getLinks.c newTree.c neatening.c searchTfIdf.c linkedList.c set.c
	gcc -Wall -Werror -g -lm  -std=c11 frequency.c getLinks.c newTree.c neatening.c searchTfIdf.c set.c linkedList.c -o searchTfidf
searchPagerank: searchPagerank.c
	gcc -Wall -Werror -g -std=c11 searchPagerank.c -o searchPagerank
clean:
	rm pagerank invertedIndex searchTfidf searchPagerank
