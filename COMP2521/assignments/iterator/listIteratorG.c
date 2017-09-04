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
    struct Node *left;
    struct Node *right;
    struct Node *lastRet;

    // Holds the relevant functions for the type of iterator
    int   (*ElmCompareFp)(void const *e1, void const *e2);
    void *(*ElmNewFp)(void const *e1);
    void  (*ElmFreeFp)(void *e1);

} IteratorGRep;
/*
static int shiftRight(IteratorG it){
    it->left = it->right;
    it->right = it->right->next;
    return 1;
}
*/

static int shiftLeft(IteratorG it){
    if(!hasPrevious(it)) {
        return 0;
    }
    it->right = it->left;
    it->left = it->left->prev;
    return 1;
}

Node * createNewNode(void *val, void *(*ElmNewFp)(void const *el))
{
    Node *newNode;
    newNode = malloc(sizeof(Node));
    newNode->next = newNode->prev = NULL;
    newNode->value = ElmNewFp(val);
    return newNode;
}

IteratorG IteratorGNew(ElmCompareFp cmpFp, ElmNewFp newFp, ElmFreeFp freeFp)
{
    IteratorG newIterator = malloc(sizeof(IteratorGRep));
    newIterator->left = newIterator->right = newIterator->lastRet = NULL;
    newIterator->ElmCompareFp = cmpFp;
    newIterator->ElmNewFp = newFp;
    newIterator->ElmFreeFp = freeFp;
    return newIterator;
}

int add(IteratorG it, void *vp)
{
    Node *newNode = createNewNode(vp, it->ElmNewFp);
    it->lastRet = NULL;
    newNode->prev = it->left;
    newNode->next = it->right;
    if(it->left != NULL) it->left->next = newNode;
    if(it->right != NULL) it->right->prev = newNode;
    it->left = newNode;
    it->right = newNode->next;

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
    it->lastRet =  it->left;
    return it->lastRet->value;
}

void * previous (IteratorG it)
{
    if(!hasPrevious(it)) {
        it->lastRet = NULL;
        return it->lastRet;
    }
    it->right = it->left;
    it->left = it->left->prev;
    it->lastRet = it->right;
    return it->lastRet->value;
}

int hasNext(IteratorG it)
{
    it->lastRet = NULL;
    return (it->right == NULL) ? 0:1;
}

int hasPrevious(IteratorG it)
{
    it->lastRet = NULL;
    return (it->left == NULL) ? 0:1;
}

void reset(IteratorG it)
{
    while(it->left!=NULL){
        if(!shiftLeft(it)) break;
    }
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
        it->lastRet = NULL;
        return 1;
    }
    if(it->left != NULL){
        it->left->next = it->right;
    }
    if(it->right != NULL){
        it->right->prev = it->left;
    }
    it->lastRet = NULL;
    return 1;
}

int set(IteratorG it, void *vp)
{
    if(it->lastRet == NULL) return 0;
    it->lastRet->value = vp;
    it->lastRet = NULL;
    return 1;
}

void *findNext(IteratorG it, void *vp)
{
    struct Node *originalLeft = it->left;
    struct Node *originalRight = it->right;
    if(originalRight == NULL) {
        it->lastRet = NULL;
        return NULL;
    }
    if(originalLeft == NULL) {
        it->left = it->right;
        it->right = it->right->next;
    }
    while(it->ElmCompareFp(vp, it->left->value) != 0){
        if(it->right == NULL) {
            it->left = originalLeft;
            it->right = originalRight;
            it->lastRet = NULL;
            return NULL;
        }
        it->left = it->left->next;
        it->right = it->right->next;
    }
    it->lastRet = it->left;
    return it->lastRet->value;
}

void *findPrevious(IteratorG it, void *vp)
{
    struct Node *originalLeft = it->left;
    struct Node *originalRight = it->right;
    if(originalLeft == NULL) {
        it->lastRet =  NULL; 
        return NULL;
    }
    if(originalRight == NULL) shiftLeft(it);
    while(it->ElmCompareFp(vp, it->right->value) != 0){
        if(it->left == NULL) {
            it->left = originalLeft;
            it->right = originalRight;
            it->lastRet = NULL;
            return NULL;
        }
        shiftLeft(it);
    }
    it->lastRet = it->right;
    return it->lastRet->value;
}

void freeIt(IteratorG it)
{
    reset(it);
    struct Node *temp = it->right;
    while(it->right != NULL) {
        it->right = it->right->next;
        it->ElmFreeFp(temp);
        temp = it->right;
    }
    free(it);
}

#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define NORM "\x1B[0m"

void printIterator(IteratorG it)
{
    struct Node *trav = it->left;
    if(trav == NULL) trav = it->right;
    if(trav == NULL) {
        printf("EMPTY LIST\n");
        return;
    }


    while(trav->prev != NULL) trav = trav->prev;
    printf("X<->");
    while(trav!=NULL) {
        int *temp = (int *) trav->value;
        if(trav == it->left){
            printf(GREEN "%d" NORM, *temp);
        }else if(trav == it->right){
            printf(RED "%d" NORM, *temp);
        }
        else{
            printf("%d", *temp);
        }
        printf("<->");
        trav = trav->next;
    }
    printf("X\n");
}

