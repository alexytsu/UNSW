// testList.c - testing DLList data type
// Written by John Shepherd, March 2013

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "DLList.h"

int main(int argc, char *argv[])
{
	DLList myList;
	myList = getDLList(stdin);
	putDLList(stdout,myList);
	assert(validDLList(myList));
	
	printf("Testing Insert Before\n");
	DLListBefore(myList, "New Line 1");
	putDLList(stdout,myList);
	assert(validDLList(myList));
	
	printf("Testing Insert Before\n");
	DLListBefore(myList, "New Line 2");
	putDLList(stdout,myList);
	assert(validDLList(myList));
	
	printf("Testing Delete: Move To Line 4 and Delete it\n");
	DLListMoveTo(myList, 4);
	DLListDelete(myList);
	putDLList(stdout,myList);
	assert(validDLList(myList));
	
	
	// TODO: more tests needed here
	return 0;
}
