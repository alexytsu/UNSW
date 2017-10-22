// set.c ... simple, inefficient Set of Strings
// Written by John Shepherd, September 2015


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "setRank.h"
#include "params.h"

#define strEQ(s,t) (strcmp((s),(t)) == 0)
#define strLT(s,t) (strcmp((s),(t)) < 0)

typedef struct Node *Link;

typedef struct Node {
	char *val;
    int pRank;
	Link  next;
} Node;
	
typedef struct SetRep {
	int   nelems;
	Link  elems;
} SetRep;

// Function signatures


static Link newNode(char *);
static void disposeNode(Link);
static int  findNode(Link,char *,Link *,Link *);


// newSet()
// - create an initially empty Set
Set newSetRank()
{
	Set new = malloc(sizeof(SetRep));
	assert(new != NULL);
	new->nelems = 0;
	new->elems = NULL;
	return new;
}

// disposeSet(Set)
// - clean up memory associated with Set
void disposeSetRank(Set s)
{
	if (s == NULL) return;
	Link next, curr = s->elems;
	while (curr != NULL) {
		next = curr->next;
		disposeNode(curr);	
		curr = next;
	}
}

// insertInto(Set,Str)
// - ensure that Str is in Set
void insertIntoRank(Set s, char *str)
{
	assert(s != NULL);
	Link curr, prev;
	int found = findNode(s->elems,str,&curr,&prev);
	if (found) return; // already in Set
	Link new = newNode(str);
	s->nelems++;
	if (prev == NULL) {
		// add at start of list of elems
		new->next = s->elems;
		s->elems = new;
	}
	else {
		// add into list of elems
		new->next = prev->next;
		prev->next = new;
	}
}

// dropFrom(Set,Str)
// - ensure that Str is not in Set
void dropFromRank(Set s, char *str)
{
	assert(s != NULL);
	Link curr, prev;
	int found = findNode(s->elems,str,&curr,&prev);
	if (!found) return;
	s->nelems--;
	if (prev == NULL)
		s->elems = curr->next;
	else
		prev->next = curr->next;
	disposeNode(curr);
}

// isElem(Set,Str)
// - check whether Str is contained in Set
int isElemRank(Set s, char *str)
{
	assert(s != NULL);
	Link curr, prev;
	return findNode(s->elems,str,&curr,&prev);
}

// nElems(Set)
// - return # elements in Set
int  nElemsRank(Set s)
{
	assert(s != NULL);
	return s->nelems;
}

// showSet(Set)
// - display Set (for debugging)
void showSetRank(Set s)
{
	Link curr;
	if (s->nelems == 0)
		printf("Set is empty\n");
	else {
		printf("Set has %d elements:\n",s->nelems);
		int id = 0;
		curr = s->elems;
		while (curr != NULL) {
			printf("[%03d] %s\n", id, curr->val);
			id++;
			curr = curr->next;
		}
	}
}

// Helper functions

static Link newNode(char *str)
{
	Link new = malloc(sizeof(Node));
	assert(new != NULL);
	new->val = malloc(PNEUMONOULTRAMICROSCOPICSILICOVOLCANOCONIOSIS*sizeof(char));
	strcpy(new->val, str);
	new->pRank = 0;
	new->next = NULL;
	return new;
}

static void disposeNode(Link curr)
{
	assert(curr != NULL);
	free(curr->val);
	free(curr);
}

// findNode(L,Str)
// - finds where Str could be added into L
// - if already in L, curr->val == Str
// - if not already in L, curr and prev indicate where to insert
// - return value indicates whether Str found or not
static int findNode(Link list, char *str, Link *cur, Link *pre)
{
	Link curr = list, prev = NULL;
	while (curr != NULL && strLT(curr->val,str)) {
		prev = curr;
		curr = curr->next;
	}
	*cur = curr; *pre = prev;
	return (curr != NULL && strEQ(str,curr->val));
}

//returns word
char *nextElemRank(Set s){
    if(s->nelems==0){
        return NULL;
    }else if(s->elems->next==NULL){
        char *tmp = malloc(PNEUMONOULTRAMICROSCOPICSILICOVOLCANOCONIOSIS*sizeof(char));
        strcpy(tmp, s->elems->val);
        free(s->elems->val);
        free(s->elems);     
        s->nelems--;   
        return tmp;        
    }else{
        Link tmp = s->elems;
        char *wordCopy = malloc(PNEUMONOULTRAMICROSCOPICSILICOVOLCANOCONIOSIS*sizeof(char));
        strcpy(wordCopy, tmp->val);        
        free(s->elems->val);
        s->elems = s->elems->next;
        free(tmp);
        s->nelems--;
        return wordCopy;    
    }
}
int isEmptyRank(Set s){
    if(s->nelems==0) return 1;
    return 0;
}

void insertPRank(Set s, int *pVector){
    assert(!isEmptyRank(s));
    int rank = 0;
    Link curr = s->elems;  
    while(curr!=NULL){
        curr->pRank = pVector[rank++];
        curr=curr->next;
    }
}


int findPRank(Set s, char *url){
    Link curr=s->elems;
printf("%s\n", url);
printf("actual set size: %d\n",nElemsRank(s));
    while(curr!=NULL && strcmp(curr->val, url)!=0){
        curr=curr->next;
    }
    int rank = curr->pRank;


    return rank;
}


void copySet(Set dest, Set src){
        Link curr = src->elems;
        while(curr!=NULL){
            insertIntoRank(dest, curr->val);
            curr=curr->next;
        }
}
