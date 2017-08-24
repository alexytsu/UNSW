#include <stdio.h>
#include "listFunctions.h"
#include "LList.h"

int square(int a)
{
	return a*a;
}

void add5(int *a)
{
	*a+=5;
}

void traverseLList1(LList L, int (*funcp)(int))
{
	LListNode *n;
	for(n = L->head; n != NULL; n = n->next){
		n->value = (*funcp)(n->value);
	}
}

void traverseLList2(LList L, void (*funcp)(int*))
{
	LListNode *n;
	for(n = L->head; n != NULL; n = n->next){
		/* (* */funcp)(&(n->value));
	}
}
