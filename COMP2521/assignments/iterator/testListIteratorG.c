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
    int *val;

    int i; 
    for(i=0; i<MAXARRAY; i++){
        printIterator(it1);
        int result = add(it1 , &a[i]);
        printf("Inserting %d: %s \n", a[i], (result==1 ? "Success" : "Failed") );
    }
    previous(it1);
    previous(it1);
    previous(it1);
    previous(it1);
    previous(it1);
    previous(it1);
    previous(it1);
    previous(it1);
    previous(it1);
    previous(it1);
    previous(it1);
    previous(it1);
    previous(it1);
    previous(it1);
    previous(it1);
    previous(it1);
    previous(it1);
    previous(it1);
    previous(it1);
    previous(it1);
    previous(it1);
    previous(it1);
    previous(it1);
    previous(it1);
    previous(it1);
    previous(it1);
    previous(it1);
    previous(it1);

    val = (int *) next(it1);
    printf("first element? %d\n", *val);

    next(it1);
    next(it1);
    next(it1);
    next(it1);
    next(it1);
    next(it1);
    next(it1);
    next(it1);
    next(it1);
    next(it1);
    next(it1);
    next(it1);
    next(it1);
    next(it1);
    next(it1);
    next(it1);
    next(it1);
    next(it1);
    next(it1);
    next(it1);
    next(it1);
    next(it1);
    next(it1);
    next(it1);
    next(it1);
    next(it1);
    next(it1);
    next(it1);
    next(it1);
    next(it1);
    
    val = (int *)previous(it1);
    printf("last element? %d\n", *val);
    delete(it1);
    next(it1);
    next(it1);
    next(it1);
    next(it1);
    val = (int *)previous(it1);
    printf("last element? %d\n", *val);

    reset(it1);
    val = (int *)next(it1);
    printf("first element after reset: %d\n", *val);


    return EXIT_SUCCESS;

}
