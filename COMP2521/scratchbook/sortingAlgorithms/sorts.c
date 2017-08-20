// Handles menial tasks for sorting algorithms such as file I/O
// Almost each action has an linked-list and array implementation
// Lists are singly linked lists with a head and tail pointer
// DLLists are doubly linked lists with a head and tail pointer
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Expected input format follows a key-value structure
// The key can be any string 5 characters long
// The value can be any positive integer
// We assume that the values are sorted and not the keys
struct item_a{
	char *key;
	int value;
};

// Reads input from a specified file and stores it in an array
// Returns number of elements on success, 0 if invalid input and -1 if out of memory
int read_file_to_array(FILE *input, struct item_a *unsorted)
{
	int array_size = 50;
	unsorted = malloc(array_size * sizeof(struct item_a));
	if(!unsorted) return -1;

	char buffer[20];

	int elements = 0;
	while(fgets(buffer, 20, input)){
		if(elements == array_size){
			array_size = array_size * 1.618;
			unsorted = realloc(unsorted, array_size * sizeof(struct item_a));
		}

		char key[20];
		if(sscanf(buffer, "%s", key) == EOF) return 0;
		strcpy(unsorted[elements].key, key);

		if(sscanf(buffer, "%d", &(unsorted[elements].value)) == EOF) return 0;

		elements++;
	}
	return elements;
}
