// removeValue.c 
// Written by Ashesh Mahidadia, August 2017

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "DLList.h"


/* 
   You will submit only this one file.

   Implement the function "removeValue" below. Read the exam paper for 
   detailed specification and description of your task.  

   - DO NOT modify code in the file DLList.h . 
   - You can add helper functions in this file.  
   - DO NOT add "main" function in this file. 

   head->prev head head->next
   head head->next
   head->prev head NULL

*/



void removeValue(DLList L, int value){
    DLListNode *head = L->first;
    DLListNode *temp = NULL;

    while(head != NULL){
        if(head->value == value){ //value to be deleted

            if(L->nitems == 1){
                free(head);
                L->first = NULL;
                L->curr = NULL;
                L->last = NULL;
                L->nitems = 0;
                return;
            }

            if(head->prev == NULL){ //if it's at the front of the list
                L->first = head->next; 
                head->next->prev = NULL;
                temp = head;
                head = head->next;
            }else if(head->next == NULL){ // if it's at the end of the list
                L->last = head->prev;
                head->prev->next = NULL;
                free(head);
                L->nitems --;
                return;
            }else {
                head->prev->next = head->next;
                head->next->prev = head->prev;
                temp = head;
                head = head->prev;
            }
            free(temp);
            L->nitems --;
        }else{  // no values removed
            head = head->next;
        }
    }

    L->curr = L->first;

    return;
}



