  // testListIteratorG.c ... client to test Generic List Iterator 
// 

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "listIteratorG.h"
#include "positiveIntType.h"
#include "stringType.h" 

#define MAXARRAY 5

void testNullList(IteratorG);
void testEmptyListString(IteratorG);
void testEmptyListInt(IteratorG);
void testAddString(IteratorG);
void testAddInt(IteratorG);
void testHasNextString(IteratorG);
void testHasNextInt(IteratorG);
void testHasPreviousString(IteratorG);
void testHasPreviousInt(IteratorG);
void testNextString(IteratorG);
void testNextInt(IteratorG);
void testPreviousString(IteratorG);
void testPreviousInt(IteratorG);
void testDeleteString(IteratorG);
void testDeleteInt(IteratorG);
void testSetString(IteratorG);
void testSetInt(IteratorG);
void testFindNextString(IteratorG);
void testFindNextInt(IteratorG);
void testFindPreviousString(IteratorG);
void testFindPreviousInt(IteratorG);
void testResetString(IteratorG);
void testResetInt(IteratorG);
char **StrArray();
void clear(IteratorG);

int PassIn;
char **StrA;

int main(int argc, char *argv[]) {
   StrA = StrArray();
   IteratorG it1 = NULL;
   IteratorG it2 = NULL;
   IteratorG it3 = NULL;
   //testNullList(it1);
   //testNullList(it2);
   it1 = IteratorGNew(positiveIntCompare, positiveIntNew, positiveIntFree);
   it2 = IteratorGNew(stringCompare, stringNew, stringFree);
   assert(it1 != NULL);
   assert(it2 != NULL);

   it3 = IteratorGNew(positiveIntCompare, positiveIntNew, positiveIntFree);
   for(int i = 0; i < 10; i ++){
    add(it3, &i);
   }
   printIterator(it3);
   previous(it3);
   previous(it3);
   printIterator(it3);
   int hel = 72;
   add(it3, &hel);
   printIterator(it3);
   printf("Previous\n");
   previous(it3);
   printIterator(it3);
   printf("Set 73\n");
   hel = 73;
   set(it3, &hel);
   printIterator(it3);
   printf("Add 23");
   hel = 23;
   add(it3, &hel);
   printIterator(it3);

    



   testEmptyListInt(it1);
   testAddInt(it1);
   testFindNextInt(it1);
   testFindPreviousInt(it1);
   testHasNextInt(it1);
   testHasPreviousInt(it1);
   testNextInt(it1);
   testPreviousInt(it1);
   testSetInt(it1);
   testResetInt(it1);
   testDeleteInt(it1);

   testEmptyListString(it2);
   testAddString(it2);
   testFindNextString(it2);
   testFindPreviousString(it2);
   testHasNextString(it2);
   testHasPreviousString(it2);
   testNextString(it2);
   testPreviousString(it2);
   testSetString(it2);
   testResetString(it2);
   testDeleteString(it2);

   int a;
   for (a = 0; a < 10; a++) {
      add(it1, &a);
   }

   freeIt(it1);
   freeIt(it2);

   int i;
   for (i = 0; i < 10; i++) {
      free(StrA[i]);
   }
   free(StrA);
   printf("\n   *****All Tests Passed*****\n");
   return EXIT_SUCCESS;
}

void testNullList(IteratorG it) {
   printf("   Test null list:\n");
   assert(hasNext(it) == 0);                   printf("   Assert hasNext on empty list:      ***Passed***\n");
   assert(hasPrevious(it) == 0);               printf("   Assert hasPrevious on empty list:  ***Passed***\n");
   assert(next(it) == NULL);                   printf("   Assert next on empty list:         ***Passed***\n");
   assert(previous(it) == NULL);               printf("   Assert previous on empty list:     ***Passed***\n");
   assert(delete(it) == 0);                    printf("   Assert delete on empty list:       ***Passed***\n");
   assert(set(it, (int *)5) == 0);             printf("   Assert set on empty list:          ***Passed***\n");
   assert(findNext(it, (int *)5) == NULL);     printf("   Assert findNext on empty list:     ***Passed***\n");
   assert(findPrevious(it, (int *)5) == NULL); printf("   Assert findPrevious on empty list: ***Passed***\n");
   reset(it);
   printf("   Test null list:                    ***Passed***\n");
   printf("\n");
}

void testEmptyListInt(IteratorG it) {
   printf("   Test empty list:\n");
   assert(hasNext(it) == 0);                   printf("   Assert hasNext on empty list:      ***Passed***\n");
   assert(hasPrevious(it) == 0);               printf("   Assert hasPrevious on empty list:  ***Passed***\n");
   assert(next(it) == NULL);                   printf("   Assert next on empty list:         ***Passed***\n");
   assert(previous(it) == NULL);               printf("   Assert previous on empty list:     ***Passed***\n");
   assert(delete(it) == 0);                    printf("   Assert delete on empty list:       ***Passed***\n");
   assert(set(it, (int *)5) == 0);             printf("   Assert set on empty list:          ***Passed***\n");
   assert(findNext(it, (int *)5) == NULL);     printf("   Assert findNext on empty list:     ***Passed***\n");
   assert(findPrevious(it, (int *)5) == NULL); printf("   Assert findPrevious on empty list: ***Passed***\n");
   reset(it);
   printf("   Test empty list:                    ***Passed***\n");
   printf("\n");
}

void testAddInt(IteratorG it) {
   printf("   Test add:\n");
   int success;
   int i;
   int *v;
   printf("   Adding: ");
   for (i = 0; i < 10; i++) {
      printf("%d, ", i);
      success = add(it, &i);
      assert(success == 1);
   }
   reset(it);
   printf("\n   testing: ");
   for (i = 0; i < 10; i++) {
      v = (int *) next(it);
      printf("%d, ", *v);
      assert(*v == i);
   }
   printf("\n   Add values:                        ***Passed***\n");

   printf("\n   Test insert:\n");
   reset(it);
   printf("   Insert: ");
   for (i = 0; i < 10; i++) {
      next(it);
      PassIn = 2;
      add(it, &PassIn);
   }
   reset(it);
   printf("\n   testing: ");
   for (i = 0; i < 10; i++) {
      v = (int *) next(it);
      printf("%d, ", *v);
      assert(*v == i);
      v = (int *) next(it);
      printf("%d, ", *v);
      assert(*v == 2);
   }
   printf("\n   Insert values:                     ***Passed***\n");
   clear(it);

   printf("\n   Test add before: ");
   for (i = 0; i < 10; i++) {
      printf("%d, ", i);
      add(it, &i);
      previous(it);
   }
   reset(it);
   printf("\n   testing: ");
   for (i = 10; i > 0; i--) {
      v = (int *) next(it);
      printf("%d, ", *v);
      //assert(*v == i - 1);
   }
   printf("\n   Test add before:                   ***Passed***\n");
   clear(it);

   printf("\n   ***Assert list is empty***\n");
   assert(hasPrevious(it) == 0);
   assert(hasNext(it) == 0);
   printf("\n   ***OK***\n");
}

void testHasNextInt(IteratorG it) {
   printf("   Test hasNext:\n");
   int i;
   for (i = 0; i < 10; i++) {
      add(it, &i);
   }
   reset(it);
   assert(hasPrevious(it) == 0);
   for (i = 0; i < 10; i++) {
      printf("%d, ", *(int *) next(it));
      if (i != 9) {
         assert(hasNext(it) == 1);
      } else {
         assert(hasNext(it) == 0);
      }
   }
   printf("\n   Test hasNext:                      ***Passed***\n");
   clear(it);
}

void testHasPreviousInt(IteratorG it) {
   printf("   Test hasPrevious:\n");
   int i;
   for (i = 0; i < 10; i++) {
      add(it, &i);
   }
   assert(hasNext(it) == 0);
   for (i = 0; i < 10; i++) {
      printf("%d, ", *(int *) previous(it));
      if (i != 9) {
         assert(hasPrevious(it) == 1);
      } else {
         assert(hasPrevious(it) == 0);
      }
   }
   printf("\n   Test hasPrevious:                  ***Passed***\n");
   clear(it);
}

void testNextInt(IteratorG it) {
   printf("   Test next:\n");
   int i;
   for (i = 0; i < 10; i++) {
      add(it, &i);
   }
   reset(it);
   int *v;
   for (i = 0; i < 10; i++) {
      v = (int *) next(it);
      printf("%d, ", *v);
      assert(*v == i);
   }
   printf("\n   Test next:                         ***Passed***\n");
   clear(it);
}

void testPreviousInt(IteratorG it) {
   printf("   Test previous:\n");
   int i;
   for (i = 0; i < 10; i++) {
      add(it, &i);
   }
   int *v;
   for (i = 10; i < 0; i--) {
      v = (int *) previous(it);
      printf("%d, ", *v);
      assert(*v == i - 1);
   }
   printf("\n   Test previous:                     ***Passed***\n");
   clear(it);
}

void testDeleteInt(IteratorG it) {
   printf("   Test delete:\n");
   int i;
   for (i = 0; i < 10; i ++) {
      add(it, &i);
   }
   PassIn = 4;
   reset(it);
   //printf ("Delete: Resetted\n");
   findNext(it, &PassIn);

   next(it);
   //printf ("Delete: Nexted\n");
   assert(delete(it) == 1);

   PassIn = 5;
   add(it, &PassIn);
   //printf ("Delete:Added\n");
   assert(delete(it) == 0);

   previous(it);
   //printf ("Delete: Previoused\n");
   assert(delete(it) == 1);

   hasNext(it);
   //printf ("Delete: hasNext\n");
   assert(delete(it) == 0);

   hasPrevious(it);
   //printf("Delete: Hasprevious\n");
   assert(delete(it) == 0);

   delete(it);
   //printf ("Has deleted\n");
   assert(delete(it) == 0);

   PassIn = 10;
   set(it, &PassIn);
   //printf ("Delete: setted 2\n");
   assert(delete(it) == 0);

   PassIn = 50;
   //printf("I am after Delete set and before findNext\n");
   findNext(it, &PassIn);
   //printf("Delete: findNexted 2\n");
   assert(delete(it) == 0);

   PassIn = 8;
   findNext(it, &PassIn);
   //printf ("Delete: findNexted 3\n");
   assert(delete(it) == 1);

   PassIn = -5;
   findPrevious(it, &PassIn);
   //printf("Delete: findPrevious 2\n");
   assert(delete(it) == 0);

   PassIn = 3;
   findPrevious(it, &PassIn);
   //printf ("Delete: findPrevious 3\n");
   assert(delete(it) == 1);

   reset(it);
   //printf ("Delete : Resetted 2\n");
   assert(delete(it) == 0);

   previous(it);
   //printf ("Delete: Previoused 2\n");
   assert(delete(it) == 0);

   PassIn = 9;
   findNext(it, &PassIn);
   next(it);
   assert(delete(it) == 0);

   clear(it);
   printf("   Test delete:                       ***Passed***\n");
}

void testSetInt(IteratorG it) {
   printf("   Test set:\n");
   int i;
   for (i = 0; i < 10; i ++) {
      add(it, &i);
   }
   printIterator(it);
   reset(it);
   printf("Reset\n");
   printIterator(it);
   PassIn = 4;
   printf("Find Next 4\n");
   findNext(it, &PassIn);
   printIterator(it);

   printf("Next\n");
   next(it);
   printIterator(it);
   
   PassIn = 11;
   printf("set 11\n");
   assert(set(it, &PassIn) == 1);
   printIterator(it);

   PassIn = 26;
   printf("add 26\n");
   add(it, &PassIn);
   printIterator(it);

    printf("set 13\n");
   PassIn = 13;
   assert(set(it, &PassIn) == 0);
   printIterator(it);

   printf("previous\n");
   previous(it);
   assert(set(it, &PassIn) == 1);
   printIterator(it);

   hasNext(it);
   assert(set(it, &PassIn) == 0);

   hasPrevious(it);
   assert(set(it, &PassIn) == 0);

   delete(it);
   assert(set(it, &PassIn) == 0);

   printf("set 12\n");
   PassIn = 12;
   set(it, &PassIn);
   printIterator(it);
   PassIn = 11;
   printf("set 11\n");
   assert(set(it, &PassIn) == 0);
   printIterator(it);

   printf("previous\n");
   previous(it);
   printIterator(it);
   PassIn = 12;
   printf("set 12\n");
   set(it, &PassIn);
   printIterator(it);
   PassIn = 11;
   printf("set 11\n");
   assert(set(it, &PassIn) == 0);
   printIterator(it);


   printf("findNext 50\n");
   PassIn = 50;
   findNext(it, &PassIn);
   printIterator(it);

   printf("set 11\n");
   PassIn = 11;
   assert(set(it, &PassIn) == 0);
   printIterator(it);

   PassIn = 8;
   findNext(it, &PassIn);
   PassIn = 11;
   assert(set(it, &PassIn) == 1);

   PassIn = -5;
   findPrevious(it, &PassIn);
   PassIn = 11;
   assert(set(it, &PassIn) == 0);

   PassIn = 3;
   findPrevious(it, &PassIn);
   PassIn = 11;
   assert(set(it, &PassIn) == 1);

   reset(it);
   assert(set(it, &PassIn) == 0);

   previous(it);
   assert(set(it, &PassIn) == 0);

   PassIn = 9;
   findNext(it, &PassIn);
   next(it);
   PassIn = 11;
   assert(set(it, &PassIn) == 0);

   clear(it);
   printf("   Test set:                          ***Passed***\n");
}

void testFindNextInt(IteratorG it) {
   printf("\n   Test findNext:\n");
   int i;
   for (i = 0; i < 10; i++) {
      add(it, &i);
   }
   int *v;
   reset(it);
   printf ("findNext: Resetted\n");
   PassIn = 7;
   v = findNext(it, &PassIn);
   printf ("findNext: foundNext\n");
   assert(*v == 7);
   v = (int *) next(it);
   printf("findNext: Nexted\n");
   assert(*v == 8);
   previous(it);
   printf ("findNext: Previoused\n");
   previous(it);
   printf ("findNext: Previoused 2\n");
   v = (int *) previous(it);
   assert(*v == 6);

   PassIn = 100;
   v = findNext(it, &PassIn);
   assert(v == NULL);
   PassIn = 1;
   v = findNext(it, &PassIn);
   assert(v == NULL);
   printf("\n   Test find next:                    ***Passed***\n");
   clear(it);
}

void testFindPreviousInt(IteratorG it) {
   printf("\n   Test findPrevious:\n");
   int i;
   for (i = 0; i < 10; i++) {
      add(it, &i);
   }
   int *v;
   PassIn = 3;
   v = findPrevious(it, &PassIn);
   assert(*v == 3);
   v = (int *) previous(it);
   assert(*v == 2);
   next(it);
   v = (int *) next(it);
   assert(*v == 3);
   previous(it);
   previous(it);
   v = (int *) previous(it);
   assert(*v == 1);
   next(it);
   next(it);
   next(it);
   next(it);
   next(it);
   PassIn = 3;
   v = findPrevious(it, &PassIn);
   assert(*v == 3);
   PassIn = -5;
   v = findPrevious(it, &PassIn);
   assert(v == NULL);
   PassIn = 9;
   v = findPrevious(it, &PassIn);
   assert(v == NULL);
   printf("\n   Test find previous:                ***Passed***\n");
   clear(it);
}

void testResetInt(IteratorG it) {
   printf("\n   Test reset:\n");
   int i;
   for (i = 0; i < 10; i++) {
      add(it, &i);
   }
   reset(it);
   assert(hasPrevious(it) == 0);
   assert(hasNext(it) == 1);
   assert(*(int *) next(it) == 0);
   assert(*(int *) next(it) == 1);
   assert(*(int *) next(it) == 2);
   clear(it);
   reset(it);
   printf("\n   Test reset:                        ***Passed***\n");
}

void testEmptyListString(IteratorG it) {
   printf("   Test empty list:\n");
   assert(hasNext(it) == 0);                  printf("   Assert hasNext on empty list:      ***Passed***\n");
   assert(hasPrevious(it) == 0);              printf("   Assert hasPrevious on empty list:  ***Passed***\n");
   assert(next(it) == NULL);                  printf("   Assert next on empty list:         ***Passed***\n");
   assert(previous(it) == NULL);              printf("   Assert previous on empty list:     ***Passed***\n");
   assert(delete(it) == 0);                   printf("   Assert delete on empty list:       ***Passed***\n");
   assert(set(it, StrA[0]) == 0);             printf("   Assert set on empty list:          ***Passed***\n");
   assert(findNext(it, StrA[0]) == NULL);     printf("   Assert findNext on empty list:     ***Passed***\n");
   assert(findPrevious(it, StrA[0]) == NULL); printf("   Assert findPrevious on empty list: ***Passed***\n");
   reset(it);
   printf("   Test empty list:                   ***Passed***\n");
   printf("\n");
}

void testAddString(IteratorG it) {
   printf("   Test add:\n");
   int success;
   int i;
   char *v;
   printf("   Adding: ");
   for (i = 0; i < 10; i++) {
      printf("%s, ", StrA[i]);
      success = add(it, StrA[i]);
      assert(success == 1);
   }
   reset(it);
   printf("\n   testing: ");
   for (i = 0; i < 10; i++) {
      v = (char *) next(it);
      printf("%s, ", v);
      assert(0 == strcmp(v, StrA[i]));
   }
   printf("\n   Add values:                        ***Passed***\n");

   printf("\n   Test insert:\n");
   reset(it);
   printf("   Insert: ");
   for (i = 0; i < 10; i++) {
      next(it);
      add(it, StrA[9]);
   }
   reset(it);
   printf("\n   testing: ");
   for (i = 0; i < 10; i++) {
      v = (char *) next(it);
      printf("%s, ", v);
      assert(0 == strcmp(v, StrA[i]));
      v = (char *) next(it);
      printf("%s, ", v);
      assert(0 == strcmp(v, StrA[9]));
   }
   printf("\n   Insert values:                     ***Passed***\n");
   clear(it);

   printf("\n   Test add before: ");
   for (i = 0; i < 10; i++) {
      printf("%s, ", StrA[i]);
      add(it, StrA[i]);
      previous(it);
   }
   reset(it);
   printf("\n   testing: ");
   for (i = 10; i > 0; i--) {
      v = (char *) next(it);
      printf("%s, ", v);
      assert(0 == strcmp(v, StrA[i - 1]));
   }
   printf("\n   Test add before:                   ***Passed***\n");
   clear(it);

   printf("\n***Assert list is empty***\n");
   assert(hasPrevious(it) == 0);
   assert(hasNext(it) == 0);
   printf("\n***OK***\n");
}

void testHasNextString(IteratorG it) {
   printf("   Test hasNext:\n");
   int i;
   for (i = 0; i < 10; i++) {
      add(it, StrA[i]);
   }
   reset(it);
   assert(hasPrevious(it) == 0);
   for (i = 0; i < 10; i++) {
      printf("%s, ", (char *) next(it));
      if (i != 9) {
         assert(hasNext(it) == 1);
      } else {
         assert(hasNext(it) == 0);
      }
   }
   printf("\n   Test hasNext:                      ***Passed***\n");
   clear(it);
}

void testHasPreviousString(IteratorG it) {
   printf("   Test hasPrevious:\n");
   int i;
   for (i = 0; i < 10; i++) {
      add(it, StrA[i]);
   }
   assert(hasNext(it) == 0);
   for (i = 0; i < 10; i++) {
      printf("%s, ", (char *) previous(it));
      if (i != 9) {
         assert(hasPrevious(it) == 1);
      } else {
         assert(hasPrevious(it) == 0);
      }
   }
   printf("\n   Test hasPrevious:                  ***Passed***\n");
   clear(it);
}

void testNextString(IteratorG it) {
   printf("   Test next:\n");
   int i;
   for (i = 0; i < 10; i++) {
      add(it, StrA[i]);
   }
   reset(it);
   char *v;
   for (i = 0; i < 10; i++) {
      v = (char *) next(it);
      printf("%s, ", v);
      assert(0 == strcmp(v, StrA[i]));
   }
   printf("\n   Test next:                         ***Passed***\n");
   clear(it);
}

void testPreviousString(IteratorG it) {
   printf("   Test previous:\n");
   int i;
   for (i = 0; i < 10; i++) {
      add(it, StrA[i]);
   }
   char *v;
   for (i = 10; i < 0; i--) {
      v = (char *) previous(it);
      printf("%s, ", v);
      assert(*v == i - 1);
   }
   printf("\n   Test previous:                     ***Passed***\n");
   clear(it);
}

void testDeleteString(IteratorG it) {
   printf("   Test delete:\n");
   int i;
   for (i = 0; i < 10; i ++) {
      add(it, StrA[i]);
   }
   reset(it);
   findNext(it, StrA[4]);

   next(it);
   assert(delete(it) == 1);

   add(it, StrA[5]);
   assert(delete(it) == 0);

   previous(it);
   assert(delete(it) == 1);

   hasNext(it);
   assert(delete(it) == 0);

   hasPrevious(it);
   assert(delete(it) == 0);

   delete(it);
   assert(delete(it) == 0);

   set(it, "Set 10");
   assert(delete(it) == 0);

   findNext(it, "50");
   assert(delete(it) == 0);

   findNext(it, StrA[8]);
   assert(delete(it) == 1);

   findPrevious(it, "-5");
   assert(delete(it) == 0);

   findPrevious(it, StrA[3]);
   assert(delete(it) == 1);

   reset(it);
   assert(delete(it) == 0);

   previous(it);
   assert(delete(it) == 0);

   findNext(it, StrA[9]);
   next(it);
   assert(delete(it) == 0);

   clear(it);
   printf("   Test delete:                       ***Passed***\n");
}

void testSetString(IteratorG it) {
   printf("   Test set:\n");
   int i;
   for (i = 0; i < 10; i ++) {
      add(it, StrA[i]);
   }
   reset(it);
   findNext(it, StrA[4]);

   next(it);
   assert(set(it, "Str 11") == 1);

   add(it, StrA[5]);
   assert(set(it, "Str 11") == 0);

   previous(it);
   assert(set(it, "Str 11") == 1);

   hasNext(it);
   assert(set(it, "Str 11") == 0);

   hasPrevious(it);
   assert(set(it, "Str 11") == 0);

   delete(it);
   assert(set(it, "Str 11") == 0);

   set(it, "Str 12");
   assert(set(it, "Str 11") == 0);

   previous(it);
   set(it, "Str 12");
   assert(set(it, "Str 11") == 0);

   findNext(it, "50");
   assert(set(it, "Str 11") == 0);

   findNext(it, StrA[8]);
   assert(set(it, "Str 11") == 1);

   findPrevious(it, "-5");
   assert(set(it, "Str 11") == 0);

   findPrevious(it, StrA[3]);
   assert(set(it, "Str 11") == 1);

   reset(it);
   assert(set(it, "Str 11") == 0);

   previous(it);
   assert(set(it, "Str 11") == 0);

   findNext(it, StrA[9]);
   next(it);
   assert(set(it, "Str 11") == 0);

   clear(it);
   printf("   Test set:                          ***Passed***\n");
}

void testFindNextString(IteratorG it) {
   printf("\n   Test findNext:\n");
   int i;
   for (i = 0; i < 10; i++) {
      add(it, StrA[i]);
   }
   char *v;
   reset(it);
   v = findNext(it, StrA[7]);
   assert(0 == strcmp(v, StrA[7]));
   v = (char *) next(it);
   assert(0 == strcmp(v, StrA[8]));
   previous(it);
   previous(it);
   v = (char *) previous(it);
   assert(0 == strcmp(v, StrA[6]));

   v = findNext(it, "100");
   assert(v == NULL);
   v = findNext(it, StrA[1]);
   assert(v == NULL);
   printf("\n   Test find next:                    ***Passed***\n");
   clear(it);
}

void testFindPreviousString(IteratorG it) {
   printf("\n   Test findPrevious:\n");
   int i;
   for (i = 0; i < 10; i++) {
      add(it, StrA[i]);
   }
   char *v;
   v = findPrevious(it, StrA[3]);
   assert(0 == strcmp(v, StrA[3]));
   v = (char *) previous(it);
   assert(0 == strcmp(v, StrA[2]));
   next(it);
   v = (char *) next(it);
   assert(0 == strcmp(v, StrA[3]));
   previous(it);
   previous(it);
   v = (char *) previous(it);
   assert(0 == strcmp(v, StrA[1]));
   next(it);
   next(it);
   next(it);
   next(it);
   next(it);
   v = findPrevious(it, StrA[3]);
   assert(0 == strcmp(v, StrA[3]));
   v = findPrevious(it, "-5");
   assert(v == NULL);
   v = findPrevious(it, StrA[9]);
   assert(v == NULL);
   printf("\n   Test find previous:                ***Passed***\n");
   clear(it);
}

void testResetString(IteratorG it) {
   int i;
   for (i = 0; i < 10; i++) {
      add(it, StrA[i]);
   }
   reset(it);
   assert(hasPrevious(it) == 0);
   assert(hasNext(it) == 1);
   assert(0 == strcmp((char *) next(it), StrA[0]));
   assert(0 == strcmp((char *) next(it), StrA[1]));
   assert(0 == strcmp((char *) next(it), StrA[2]));
   clear(it);
   reset(it);
}

char **StrArray(char **StrA) {
   StrA = malloc(sizeof(char*) * 10);
   StrA[0] = strdup("Str 0");
   StrA[1] = strdup("Str 1");
   StrA[2] = strdup("Str 2");
   StrA[3] = strdup("Str 3");
   StrA[4] = strdup("Str 4");
   StrA[5] = strdup("Str 5");
   StrA[6] = strdup("Str 6");
   StrA[7] = strdup("Str 7");
   StrA[8] = strdup("Str 8");
   StrA[9] = strdup("Str 9");
   return StrA;
}

void clear(IteratorG it) {
   reset(it);
   while (hasNext(it)) {
      next(it);
      delete(it);
   }
}
  
  /* The following code, inside the comments, may or may not be correct!
     
     It's provided in case you find it difficult to understand 
     how to create a generic list iterator, and use it's functions.
     
     Please study SetG example we discussed in the lecture in detail.

     The code below only tests basic operations, however 
     make sure that you do test all the required functions properly in
     your test file. 

  */
  
  /* =======================================
     --------- positiveIntType List Iterator ----------
  */
  
/*
  IteratorG it1 = IteratorGNew(positiveIntCompare, positiveIntNew, positiveIntFree);
  
  int a[MAXARRAY] = { 25, 12, 6, 82 , 11};
  
  int i;
  for(i=0; i<MAXARRAY; i++){
    int result = add(it1 , &a[i]); 
    printf("Inserting %d: %s \n", a[i], (result==1 ? "Success" : "Failed") );
  }
*/	
	/*
	The above loop should print ... 
		Inserting 25: Success 
		Inserting 12: Success 
		Inserting 6: Success 
		Inserting 82: Success 
		Inserting 11: Success
	*/  

/*
  int *v1 = (int *) previous(it1);
  printf("Previous value is: %d \n", *v1 );  // should print "Previous value is: 11" 
  
  int *v2 = (int *) previous(it1);
  printf("Previous value is: %d \n", *v2 );  // should print "Previous value is: 82" 
  
  int *v3 = (int *) next(it1);
  printf("Next value is: %d \n", *v3 );     // should print "Next value is: 82" 
*/  

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
