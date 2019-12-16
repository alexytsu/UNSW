#include <stdio.h>
#include <stdlib.h>
#include "LList.h"
#include "listFunctions.h"

int main(void) {
	LList list = newLList();
	populateLList(list, stdin);

	printf("===== Original List =====\n");
	printLList(list);

	int (*funcp)(int) = square;
	traverseLList1(list, (*funcp));

	printf("===== Squared List =====\n");
	printLList(list);

	void (*vfuncp)(int*) = add5;
	traverseLList2(list, (*vfuncp));

	printf("===== Added 5 to list =====\n");
	printLList(list);
}
