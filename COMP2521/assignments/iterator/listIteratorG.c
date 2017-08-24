/*
	listIteratorG.c ... Generic List Iterator implementation
	Written by Alexander Su (z5166086)
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "listIteratorG.h"

typedef struct Node {
	// Implement the nodes as elements in a doubly linked list that hold void
	// pointers
	void *value;
	struct Node *next;
	struct Node *prev;
} Node;

typedef struct IteratorGRep {
	int nelems;

	// abs(cursorPos) gives the position of the cursor. If cursosPos is negative
	// then its position before curr, if positive it comes after curr
	int cursorPos;

	// Holds the beginning, end and last returned node of the iterator
	struct Node *head;
	struct Node *tail;
	struct Node *curr;

	// Holds the relevant functions for the type of iterator
	int   (*ElmCompareFp)(void const *e1, void const *e2);
	void *(*ElmNewFp)(void const *e1);
	void  (*ElmFreeFp)(void *e1);

} IteratorGRep;

Node * createNewNode(void *val)
{
	Node *newNode;
	newNode = malloc(sizeof(Node));
	newNode->next = newNode->prev = NULL;
	newNode->value = val;
	return newNode;
}

IteratorG IteratorGNew(ElmCompareFp cmpFp, ElmNewFp newFp, ElmFreeFp freeFp)
{
	IteratorG newIterator = malloc(sizeof(IteratorGRep));
	newIterator->head = newIterator->tail = newIterator->curr = NULL;
	newIterator->cursorPos = 0;
	newIterator->nelems = 0;
	newIterator->ElmCompareFp = cmpFp;
	newIterator->ElmNewFp = newFp;
	newIterator->ElmFreeFp = freeFp;
	return newIterator;
}

int  add(IteratorG it, void *vp)
{
	Node *newNode = createNewNode(vp);

	if(it->nelems == 0){
		it->head = it->tail = it->curr = newNode;
		it->cursorPos = 1;
	}else{
		Node *before;
		Node *after;
		if(it->cursorPos > 0){
			before = it->curr;
			after = it->curr->next;
			it->cursorPos ++;
		}else if(it->cursorPos < 0){
			before = it->curr->prev;
			after = it->curr;
			it->cursorPos = it->cursorPos * -1 + 1;
		}else{
			return 0;
		}
		if(before != NULL) before->next = newNode;
		if(after != NULL) after->prev = newNode;
		newNode->prev = before;
		newNode->next = after;
	}
	it->curr = newNode;
	it->nelems ++;
	return 1;
}

void printIteratorG(IteratorG it)
{
	Node *N;
	for(N = it->head; N != NULL; N = N->next){
		int *val = (int *) N->value;
		printf(" [%d]->", *val);
	}
	printf(" [X]\n");
	int i;
	int cursor = abs(it->cursorPos);
	for(i = 0; i < it->nelems * 2 + 1; i ++){
		if(i == cursor*2) printf("%c", it->cursorPos > 0 ? '<':'>');
		else printf("%s", (i%2 == 0) ? ".":"     ");
	}
	printf("\n");
}

void *previous(IteratorG it)
{
	Node *prev;
	if(it->cursorPos == 0){
		return NULL;
	}else if(it->cursorPos < 0){
		prev = it->curr->prev;
		it->cursorPos = it->cursorPos * -1 + 1;
	}else{
		prev = it->curr;
		it->cursorPos --;
	}
	it->curr = it->curr->prev;
	return prev->value;
}

void *next(IteratorG it) // some funny business going on atm
{
	Node *next;
	assert(it->cursorPos <= it->nelems * 2 + 1);
	if(abs(it->cursorPos) == it->nelems* 2 + 1){
		return NULL;
	}else if(it->cursorPos < 0){
		next = it->curr;
		it->cursorPos --;
	}else{
		next = it->curr->next;
		it->cursorPos = it->cursorPos * -1  -1;
	}
	it->curr = it->curr->next;
	return next->value;
}

void reset(IteratorG it)
{
	it->cursorPos = 0;
	it->curr = it->head;
}

void freeIt(IteratorG it)
{
	Node *N;
	Node *P = NULL;
	for(N = it->head; N != NULL; N = N->next){
		free(P);
		P = N;
	}
	free(P);
	free(it);
}
