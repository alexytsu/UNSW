// testList.c - testing DLList data type
// Written by John Shepherd, March 2013

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "DLList.h"

#define BEFORE 0 
#define AFTER 1

void printStatus(char *message)
{
    printf("\n===== %s =====\n", message);    
}

int main(int argc, char *argv[])
{
    char * filename;
    if(argc == 1){
        printf("Usage: ./testL [file1] [file2] [file3] ... \n");
        printf("Please enter the names of the files you wish to test\n");
        return 1;
    }

    int i;
    for(i = 1, filename = argv[i]; i < argc; filename = argv[++i]){
        FILE * fin = fopen(filename, "r");

        // Read a set of lines from a specified file
        DLList myList;
        printf("**************** Getting input from '%s'", filename);
        printf("****************\n");
        myList = getDLList(fin);

        // Implement the tests
        
        // Print the details of the unmodified list
        printStatus("Original file");
        details(myList, BEFORE);
        putDLList(stdout,myList);
        assert(validDLList(myList));

        // Insert a new first line
        printStatus("Testing Insert Before");
        details(myList, BEFORE);
        DLListBefore(myList, "New Line 1");

        details(myList, AFTER);
        putDLList(stdout,myList);
        assert(validDLList(myList));

        // Insert again a new first line
        printStatus("Testing Insert Before");
        details(myList, BEFORE);
        DLListBefore(myList, "New Line 2");

        details(myList, AFTER);
        putDLList(stdout,myList);
        assert(validDLList(myList));


        // Test moving to line numbers and deleting them
        printStatus("Testing Delete: Move To Line 4 and Delete it");
        details(myList, BEFORE);
        DLListMoveTo(myList, 4);
        DLListDelete(myList);
        
        details(myList, AFTER);
        putDLList(stdout,myList);
        assert(validDLList(myList));

    }
    return 0;
}
