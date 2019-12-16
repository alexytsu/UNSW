// A bubble sort with early exit which is stable
#include <stdio.h>
#include <stdlib.h>
#include "sorts.h"

int main(int argc, char *argv[])
{

	if(argc == 1){
		fprintf(stderr, "Expected an argument.\n Usage: ./bubblesort [filename] [outputname (optional)]\n");
		return 1;
	}

	Item_array *unsorted;
	FILE *fin = fopen(argv[1], "r");
	int list_size = read_file_to_array(fin, *unsorted);

	for(int i = 0; i < list_size; i ++){
		printf("%d\n", unsorted[i].value);
	}

	return 0;
}
