/*
  testListIteratorG.c ... Unit tests for my implementation of an Iterator
	Written by Alexander Su (z5166086)
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "listIteratorG.h"
#include "positiveIntType.h"
#include "stringType.h"

#define MAXARRAY 5

int main(int argc, char *argv[])
{
  /* =======================================
     --------- positiveIntType List Iterator ----------
  */

  IteratorG it1 = IteratorGNew(positiveIntCompare, positiveIntNew, positiveIntFree);

  int a[MAXARRAY] = { 25, 12, 6, 82 , 11};

  int i; 
  for(i=0; i<MAXARRAY; i++){
    int result = add(it1 , &a[i]);
    printf("Inserting %d: %s \n", a[i], (result==1 ? "Success" : "Failed") );
    printIteratorG(it1);
  }
	/*
	The above loop should print ...
		Inserting 25: Success
		Inserting 12: Success
		Inserting 6: Success
		Inserting 82: Success
		Inserting 11: Success
	*/

  int *v1 = (int *) previous(it1);
  printf("Previous value is: %02d \n", *v1 );  // should print "Previous value is: 11"
	printIteratorG(it1);

  int *v2 = (int *) previous(it1);
  printf("Previous value is: %02d \n", *v2 );  // should print "Previous value is: 82"
	printIteratorG(it1);

  int *v3 = (int *) next(it1);
  printf("Next value is: %02d \n", *v3 );     // should print "Next value is: 82"
	printIteratorG(it1);

  int *v5 = (int *) previous(it1);
  printf("Previous value is: %02d \n", *v5 );  // should print "Previous value is: 82"
	printIteratorG(it1);

  int *v4 = (int *) next(it1);
  printf("Next value is: %02d \n", *v4 );     // should print "Next value is: 82"
	printIteratorG(it1);

  /* =======================================
     --------- stringType List Iterator ----------
  */

/*
  IteratorG it2 = IteratorGNew(stringCompare, stringNew, stringFree);

  char *strA[MAXARRAY];
  strA[0] = strdup("john");
  strA[1] = strdup("rita");
  strA[2] = strdup("john");
  strA[3] = strdup("abby");

  int j;
  for(j=0; j<4; j++){
    int result = add(it2 , strA[j]);
    printf("Inserting %s: %s \n", strA[j], (result==1 ? "Success" : "Failed") );
  }
*/
	/*
	The above loop should print ...
		Inserting john: Success
		Inserting rita: Success
		Inserting john: Success
		Inserting abby: Success
	*/
/*
  char *v4 = (char *) previous(it2);
  printf("Previous value is: %s \n", v4 );  // should print: "Previous value is: abby"

  char *v5 = (char *) previous(it2);
  printf("Previous value is: %s \n", v5 );  // should print: "Previous value is: john"

  char *v6 = (char *) next(it2);
  printf("Next value is: %s \n", v6 );      // should print: "Next value is: john"

*/
  return EXIT_SUCCESS;

}
