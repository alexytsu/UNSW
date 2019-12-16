#ifndef LLIST_H
#define LLIST_H

#include <stdio.h>

typedef struct LListNode{
	int value;
	struct LListNode *next;
}LListNode;

typedef struct LListRep{
	int nelems;
	LListNode *head;
	LListNode *tail;
	LListNode *curr;
}LListRep;

typedef struct LListRep *LList;

LList newLList();

void populateLList(LList L, FILE *input);

void appendToLList(LList L, int val);

void prependToLList(LList L, int val);

void printLList(LList L);

void insertPosLList(LList L, int val, int pos);

void insertOrderedLList(LList L, int val);

#endif
