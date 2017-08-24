#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    int value;
    char *identifier;
    struct node *next;
}Node;

typedef struct list{
    struct node *head;
    struct node *tail;
    int size;
}List;

List *createNewList()
{
    List *newList = malloc(sizeof(List));
    newList->size = 0;
    newList->head = NULL;
    newList->tail = NULL;
    return newList;
}

Node *createNewNode(int val, char* id)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->identifier = malloc(10*sizeof(char));
    strcpy(newNode->identifier, id);
    newNode->value = val;
    newNode->next = NULL;
    return newNode; 
}

void append(Node *new, List *old)
{
    if(old->head == NULL){
        old->head = new;
    }
    if(old->tail) old->tail->next = new;
    old->tail = new;
    old->size++;
}

int readFromFile(FILE *fin, List *newList)
{
    char buffer[30] = {0};
    Node *temp;
    int val;
    char id[20];
    while(fgets(buffer, 30, fin)){
        sscanf(buffer, "%d %s", &val, &id);
        temp = createNewNode(val, id);
        append(temp, newList);
    }
    return 1;
}

void printList(List *list)
{
    Node *temp;
    for(temp = list->head; temp != NULL; temp = temp->next){
        printf("%d %s\n", temp->value, temp->identifier);
    }
}

void swap(Node *a, Node *b)
{
    int temp = a->value;
    char *tempid = a->identifier;
    a->value = b->value;
    a->identifier = b->identifier;
    b->value = temp;
    b->identifier = tempid;
}

void bubbleSort(List *input)
{
    int swapped, i;
    Node *ptr1 = input->head;
    Node *lptr = NULL;

    if(ptr1 == NULL) return;

    do{
        swapped = 0;
        ptr1 = input->head; 

        while(ptr1->next != lptr){
            if(ptr1->value > ptr1->next->value){
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}

int main(void)
{
    List *input = createNewList();
    FILE *random_duplicates = fopen("duplicates", "r");
    readFromFile(random_duplicates, input);
    //printList(input);
    //printf("================= Beginning bubble sort ==================\n");
    bubbleSort(input);
    //printf("================= Sorted list ============================\n");
    printList(input);

}
