#include <stdio.h>
#include "LList.h"

#ifndef LIST_FUNCTIONS_H
#define LIST_FUNCTIONS_H

int square(int a);
void add5(int *a);
void traverseLList1(LList L, int (*funcp)(int));
void traverseLList2(LList L, void (*funcp)(int*));

#endif
