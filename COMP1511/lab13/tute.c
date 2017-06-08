#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *next;
};

struct node *add(int i, struct node *list){
    struct node *new = malloc(sizeof(struct node));
    new->data = i;
    new->next = list;
    return new;
}

void printlist(struct node *list){
    while(list!=NULL){
        printf("[%d]->", list->data);
    }
    printf("X\n");
}

int main(void){
    struct node *list1 = NULL;
    list1 = add(1, list1);
    list1 = add(2, list1);
    list1 = add(3, list1);
    printlist(list1);
}

