#include <stdio.h>
#include <stdlib.h>
#include "LList.h"

LListNode *newLListNode(int val)
{
	LListNode *newNode;

	newNode = malloc(sizeof(LListNode));
	newNode->value = val;
	newNode->next = NULL;

	return newNode;
}

LList newLList()
{
	LList newList;

	newList = malloc(sizeof(LListRep));
	newList->nelems = 0;
	newList->head = newList->tail = newList->curr = NULL;

	return newList;
}

void populateLList(LList L, FILE *input)
{
	char buffer[5];
	int val;
	while(fgets(buffer, 5, input)){
		sscanf(buffer, "%d", &val);
		appendToLList(L, val);
	}
}

void appendToLList(LList L, int val)
{
	L->nelems++;
	LListNode *n = newLListNode(val);

	if(L->head == NULL){
		L->head = L->curr = L->tail = n;
		return;
	}
	L->tail->next = n;
	L->tail = n;
}

void prependToLList(LList L, int val)
{
	L->nelems++;
	LListNode *n = newLListNode(val);

	n->next = L->head;
	L->head = n;
}

void printLList(LList L)
{
	LListNode *newNode;
	for(newNode = L->head; newNode != NULL; newNode = newNode->next){
		printf("[%d] -> ", newNode->value);
	}
	printf("X\n");
}

void insertPosLList(LList L, int val, int pos)
{
	//TODO	implement a position insert
	return;
}

void insertOrderedLList(LList L, int val)
{
	//TODO	implement an ordered insert
	return;
}
