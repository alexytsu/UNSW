// testList.c - testing DLList data type
// Written by John Shepherd, March 2013

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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

    DLList stdinList;
    stdinList = getDLList(stdin);
    putDLList(stdout,stdinList);

    // used to test when deleting form a list of two lines
    DLListDelete(stdinList);
    assert(validDLList(stdinList));

    printStatus("Passed manual tests!");

    int i;
    for(i = 1, filename = argv[i]; i < argc; filename = argv[++i]){
        FILE * fin = fopen(filename, "r");
        // Read a set of lines from a specified file
        DLList myList;
        printf("**************** Getting input from '%s'", filename);
        printf("****************\n");
        myList = getDLList(fin);

        if(strcmp(filename, "tests/empty")){ //separate tests for an empty file
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

                // Move to line 5 and insert after
                printStatus("Move to Line 5 and insert after");
                details(myList, BEFORE);
                DLListMoveTo(myList, 5);
                DLListAfter(myList, "After line 5");

                details(myList, AFTER);
                putDLList(stdout,myList);
                assert(validDLList(myList));

                // Move to line 7 and insert after
                printStatus("Move to Line 7 and insert after");
                details(myList, BEFORE);
                DLListMoveTo(myList, 7);
                DLListAfter(myList, "After line 7");

                details(myList, AFTER);
                putDLList(stdout,myList);
                assert(validDLList(myList));

                // Test insert before from the bottom of the list
                printStatus("Insert above from list bottom");
                details(myList, BEFORE);
                DLListBefore(myList, "Above last line");

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

                // Try delete more lines than the file has
                while(DLListLength(myList) > 0){
                    printStatus("Testing delete in loop");
                    printf("List is %d elements long\n", DLListLength(myList));
                    printf("Deleting current line!\n");
                    DLListDelete(myList);
                    printf("Deleted. Now the file looks like\n");
                    putDLList(stdout,myList);
                    assert(validDLList(myList));
                }

                printStatus("Deleting an empty list!");
                DLListDelete(myList);
                printf("Deleted. Now the file looks like\n");
                putDLList(stdout,myList);
                assert(validDLList(myList));
        }else{
            printStatus("Insert before an empty list");
            DLListBefore(myList, "New First Line");
            printf("Inserted\n");
            putDLList(stdout,myList);
            assert(validDLList(myList));

            while(DLListLength(myList) > 0){
                printStatus("Testing delete in loop");
                printf("List is %d elements long\n", DLListLength(myList));
                printf("Deleting current line!\n");
                DLListDelete(myList);
                printf("Deleted. Now the file looks like\n");
                putDLList(stdout,myList);
                assert(validDLList(myList));
            }

            printStatus("Insert after an empty list");
            DLListBefore(myList, "New Last Line");
            printf("Inserted\n");
            putDLList(stdout,myList);
            assert(validDLList(myList));
             

        }


    }
    return 0;
}
