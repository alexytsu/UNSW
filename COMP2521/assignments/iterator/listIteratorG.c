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
    struct Node *left;
    struct Node *right;
    struct Node *lastRet;

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
    newIterator->left = newIterator->right = newIterator->lastRet = NULL;
    newIterator->nelems = 0;
    newIterator->ElmCompareFp = cmpFp;
    newIterator->ElmNewFp = newFp;
    newIterator->ElmFreeFp = freeFp;
    return newIterator;
}

int  add(IteratorG it, void *vp)
{
    Node *newNode = createNewNode(vp);

    it->nelems ++;
    newNode->prev = it->left;
    newNode->next = it->right;
    if(it->left != NULL) it->left->next = newNode;
    if(it->right != NULL) it->right->prev = newNode;
    it->left = newNode;
    //adding to empty list

    return 1;
}

void * next(IteratorG it)
{ 
    if(!hasNext(it)){
        it->lastRet = NULL;
        return it->lastRet;
    }
    it->left = it->right;
    it->right = it->right->next;
    it->lastRet =  it->left->value;
    return it->lastRet;
}

void * previous (IteratorG it)
{
    if(!hasPrevious(it)) {
        it->lastRet = NULL;
        return it->lastRet;
    }
    it->right = it->left;
    it->left = it->left->prev;
    it->lastRet = it->right->value;
    return it->lastRet;
}

int hasNext(IteratorG it)
{
    return (it->right == NULL) ? 0:1;
}

int hasPrevious(IteratorG it)
{
    return (it->left == NULL) ? 0:1;
}

void reset(IteratorG it)
{
    while(it->left->prev!=NULL){
        it->left = it->left->prev;
    }
    it->right = it->left;
    it->left = NULL;
    it->lastRet = NULL;
}

int delete(IteratorG it){
    if(it->lastRet == NULL) return 0; 
    if(it->lastRet == it->right){
        it->right = it->right->next;
    }else if(it->lastRet == it->left){
        it->left = it->left->prev;
    }else{
        struct Node *tempRight = it->lastRet->next;
        struct Node *tempLeft = it->lastRet->prev;
        if(tempLeft != NULL){
            tempLeft->next = tempRight;
        }
        if(tempRight != NULL){
            tempRight->prev = tempLeft;
        }
        free(it->lastRet->value);
        free(it->lastRet);
        it->nelems --;
        return 1;
    }
    free(it->lastRet->value);
    free(it->lastRet);
    it->nelems --;
    if(it->left != NULL){
        it->left->next = it->right;
    }
    if(it->right != NULL){
        it->right->prev = it->left;
    }
    return 1;
}

void printIterator(IteratorG it)
{
    struct Node *trav = it->left;
    if(trav == NULL) trav = it->right;
    if(trav == NULL) {
        printf("Empty Iterator\n Number of elements: %d \n", it->nelems);
        return;
    }

    while(trav->prev != NULL) trav = trav->prev;
    while(trav->next !=NULL) {
        int *temp = (int *) trav->value;
        printf("%d->", *temp);
        trav = trav->next;
    }
    printf("X\n");

}

