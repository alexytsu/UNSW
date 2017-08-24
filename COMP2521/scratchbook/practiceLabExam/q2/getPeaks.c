// getPeaks.c 
// Written by Ashesh Mahidadia, August 2017

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "DLList.h"


/* 
   You will submit only this one file.

   Implement the function "getPeaks" below. Read the exam paper for 
   detailed specification and description of your task.  

   - DO NOT modify code in the file DLList.h . 
   - You can add helper functions in this file.  
   - DO NOT add "main" function in this file. 

   headprev head headnext

*/

void insertNth(DLList L, int tempValue, int pos){


    DLListNode *temp = newDLListNode(tempValue);
    DLListNode *head = L->first; 
    int curpos = 1;
    while(curpos < pos && head != NULL){
        head = head->next;
        curpos ++;
    }

    if(pos == 1){
        temp->next = L->first;
        L->first->prev = temp;
        L->first = temp;
        L->nitems ++;
        return;
    }

    head->prev->next = temp;
    temp->next = head;
    temp->prev = head->prev;
    head->prev = temp;

    L->nitems ++;
}

void appendToList(DLList L, DLListNodeP temp){
    if(L->curr == NULL){
        L->first = temp;
        L->last = temp;
        L->curr = temp;
    }else{
        L->last->next = temp;
        temp->prev = L->last;
        L->last = temp;
    }
    L->nitems ++;
}

DLList getPeaks(DLList L){

    DLList peaksL = newDLList();
    DLListNode *checker = L->first->next; 
    DLListNode *temp = NULL;

    if (L->nitems < 3) return peaksL;

    while(checker->next != NULL){
        if(checker->next->value < checker->value && checker->prev->value < checker->value){
            temp = newDLListNode(checker->value);
            appendToList(peaksL, temp);
        }
        checker = checker->next;
    }


    return peaksL;
}



