// DLList.c - Implementation of doubly-linked list ADT
// Written by John Shepherd, March 2013
// Modified by John Shepherd, August 2014, August 2015

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "DLList.h"

// data structures representing DLList

typedef struct DLListNode {
	char   *value;  // value of this list item (string)
	struct DLListNode *prev;
	               // pointer previous node in list
	struct DLListNode *next;
	               // pointer to next node in list
} DLListNode;

typedef struct DLListRep {
	int  nitems;      // count of items in list
	DLListNode *first; // first node in list
	DLListNode *curr;  // current node in list
	DLListNode *last;  // last node in list
} DLListRep;

// create a new DLListNode (private function)
static DLListNode *newDLListNode(char *it)
{
	DLListNode *new;
	new = malloc(sizeof(DLListNode));
	assert(new != NULL);
	new->value = strdup(it);
	new->prev = new->next = NULL;
	return new;
}

// create a new empty DLList
DLList newDLList()
{
	struct DLListRep *L;

	L = malloc(sizeof (struct DLListRep));
	assert (L != NULL);
	L->nitems = 0;
	L->first = NULL;
	L->last = NULL;
	L->curr = NULL;
	return L;
}

// free up all space associated with list
void freeDLList(DLList L)
{
	assert(L != NULL);
	DLListNode *curr, *prev;
	curr = L->first;
	while (curr != NULL) {
		prev = curr;
		curr = curr->next;
		free(prev->value);
		free(prev);
	}
	free(L);
}

// trim off \n from strings (private function)
// this is needed for getDLList() because of fgets()
// alternatively, we could use the evil gets() function
static char *trim(char *s)
{
	int end = strlen(s)-1;
	if (s[end] == '\n') s[end] = '\0';
	return s;
}

// create an DLList by reading items from a file
// assume that the file is open for reading
// assume one item per line, line < 999 chars
DLList getDLList(FILE *in)
{
	DLList L;
	DLListNode *new;
	char line[1000];

	L = newDLList();
	while (fgets(line,1000,in) != NULL) {
		char *value = strdup(trim(line));
		new = newDLListNode(value);
		if (L->last == NULL) {
			L->first = L->last = new;
		}
		else {
			L->last->next = new;
			new->prev = L->last;
			L->last = new;
		}
		L->nitems++;
	}	
	L->curr = L->first;
	return L;
}

// display list to file, one item per line
// assumes that the file is open for writing
void putDLList(FILE *out, DLList L)
{
	assert(out != NULL); assert(L != NULL);
	DLListNode *curr;
	for (curr = L->first; curr != NULL; curr = curr->next)
		fprintf(out,"%s\n",curr->value);
}

// check sanity of a DLList (for testing)
int validDLList(DLList L)
{
	if (L == NULL) {
		fprintf(stderr,"DLList is null\n");
		return 0;
	}
	if (L->first == NULL) {
		// list is empty; curr and last should be null
		if (L->last != NULL || L->curr != NULL) {
			fprintf(stderr,"Non-null pointers in empty list\n");
			return 0;
		}
	}
	else {
		// list is not empty; curr and last should be non-null
		if (L->last == NULL || L->curr == NULL) {
			fprintf(stderr,"Null pointers in non-empty list\n");
			return 0;
		}
	}
	int count;
	DLListNode *curr;
	// check scanning forward through list
	count = 0;
	for (curr = L->first; curr != NULL; curr = curr->next) {
		if (curr->prev != NULL && curr->prev->next != curr) {
			fprintf(stderr, "Invalid forward link into node (%s)\n",curr->value);
			return 0;
		}
		if (curr->next != NULL && curr->next->prev != curr) {
			fprintf(stderr, "Invalid backward link into node (%s)\n",curr->value);
			return 0;
		}
		count++;
	}
	if (count != L->nitems) {
		fprintf(stderr, "Forward count mismatch; counted=%d, nitems=%d\n",
		        count, L->nitems);
		return 0;
	}
	// check scanning backward through list
	count = 0;
	for (curr = L->last; curr != NULL; curr = curr->prev) {
		count++;
	}
	if (count != L->nitems) {
		fprintf(stderr, "Backward count mismatch; counted=%d, nitems=%d\n",
		        count, L->nitems);
		return 0;
	}
	// nothing went wrong => must be ok
	return 1;
}

// return item at current position
char *DLListCurrent(DLList L)
{
	assert(L != NULL); assert(L->curr != NULL);
	return L->curr->value;
}

// move current position (+ve forward, -ve backward)
// return 1 if reach end of list during move
// if current is currently null, return 1
int DLListMove(DLList L, int n)
{
	assert(L != NULL);
	if (L->curr == NULL)
		return 1;
	else if (n > 0) {
		while (n > 0 && L->curr->next != NULL) {
			L->curr = L->curr->next;
			n--;
		}
	}
	else if (n < 0) {
		while (n < 0 && L->curr->prev != NULL) {
			L->curr = L->curr->prev;
			n++;
		}
	}
	return (L->curr == L->first || L->curr == L->last) ? 1 : 0;
}

// move to specified position in list
// i'th node, assuming first node has i==1
int DLListMoveTo(DLList L, int i)
{
	assert(L != NULL); assert(i > 0);
	L->curr = L->first;
	return DLListMove(L, i-1);
}

// insert an item before current item
// new item becomes current item
void DLListBefore(DLList L, char *it)
{
	assert(L != NULL);
    DLListNode *newNode = newDLListNode(it);
    if(L->curr == NULL){
        L->first=L->curr=L->last=newNode;
    }else if(L->curr->prev==NULL){
        newNode->next = L->curr;
        L->curr->prev = newNode;
        L->first = newNode;
    }
    else{
	    L->curr->prev->next = newNode; 
	    newNode->next = L->curr;
	    newNode->prev = L->curr->prev;
	    L->curr->prev = newNode;
	}
	L->curr = newNode;
	L->nitems++;
}

// insert an item after current item
// new item becomes current item
void DLListAfter(DLList L, char *it)
{
	assert(L != NULL);
	DLListNode *newNode = newDLListNode(it);
    newNode->prev = L->curr; 
	newNode->next = L->curr->next;
    if(L->curr->next != NULL){ //inserting at the end of a list
	    L->curr->next->prev = newNode;
    }else{
        L->last = newNode;
    }
	L->curr->next = newNode;
	L->curr = newNode;
	
	L->nitems++;
}

// delete current item
// new item becomes item following current
// if current was last, current becomes new last
// if current was only item, current becomes null
void DLListDelete(DLList L)
{
	assert (L != NULL);
    if(L->curr==NULL) return;
	if(L->curr->prev==NULL && L->curr->next==NULL){ //last one 
        free(L->curr); 
        L->first = NULL;
        L->last = NULL;
	    L->curr = NULL;
        L->nitems = 0;
        return;
	}
	else if(L->curr->next==NULL){ //last
	    DLListNode *newcurr = L->curr->prev;
	    L->curr->prev->next = NULL;
	    free(L->curr);
	    L->curr = newcurr;
	    L->last = newcurr;
	}
	else if(L->curr->prev==NULL){ //first
	    DLListNode *newcurr = L->curr->next;
	    L->curr->next->prev = NULL;
	    free(L->curr);
	    L->curr = newcurr;
	    L->first = newcurr;
	}
	else{
	    L->curr->prev->next = L->curr->next;
	    L->curr->next->prev = L->curr->prev;
	    DLListNode *newcurr = L->curr->next;
	    free(L->curr);
	    L->curr = newcurr;
	}
    L->nitems--;
}

// return number of elements in a list
int DLListLength(DLList L)
{
	return (L->nitems);
}

// is the list empty?
int DLListIsEmpty(DLList L)
{
	return (L->nitems == 0);
}

#define CYAN "\x1b[36m"
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"

void details(DLList myList, int state)
{

    (state) ? printf(CYAN):printf(GREEN);
    printf("Details %s\n", (state) ? "after":"before");
    printf("nitems: %d\n", myList->nitems);
    printf("first: %s\n", myList->first->value);
    printf("last: %s\n", myList->last->value);
    printf("curr: %s\n", myList->curr->value);
    if(state){
        printf("\n\n List contents after this change \n\n");
    }
    printf(RESET);
}
