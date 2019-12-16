// testRemoveValue.h 
// Written by Ashesh Mahidadia, August 2017

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "DLList.h"
#include "removeValue.h"


int main(int argc, char *argv[])
{
	int value;
	if(fscanf(stdin, "%d", &value) != 1){
		fprintf(stderr, ">>> Error: Invalid input! \n");
		return 1;
	}
	DLList L = getDLList(stdin);

	fprintf(stdout, "Value: %d\n" , value);
	fprintf(stdout, "Input sequence: ");
	putDLList(stdout, L);

	removeValue(L, value);
	int validList = validDLList(L);
	if( ! validList ) {
		fprintf(stderr, ">>> Error: Invalid list returned from the function removeValue! \n");
		return 1;
	}

	fprintf(stdout, "After removal: ");
	putDLList(stdout, L);

	freeDLList(L);

	return 0;

}
