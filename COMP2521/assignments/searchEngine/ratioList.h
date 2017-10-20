#include <stdio.h>
#include "params.h"


typedef struct node{
    char *url;	//stores url obviously
    double ratio;
    struct node *next;
}node;

typedef struct listRep{
    struct node *first;
    struct node *last;
    int length;
}listRep;


typedef struct node *Node;
typedef struct listRep *List;

List newList();
Node newListNode(char*page);  //nodes created with no ratio, they are added later on

void addList(List l, char *page); //adds page into list
void insertOrder(List l, char *v); //inserts n in alphabetical order into l

void removeNext(List l, Node keep); //removes element after keep
void filterList(List l);        //filters out duplicates in list

void calculateRatio(List l, int rank);  //assigns a ratio to each url respective to its rank in a specific file/list
void combineLists(List dest, List src); //merge src into dest with duplicates
void copyList(List dest, List src);   //copies src into dest sorted alphabetically
void computeAvgRatio(List l);   //searches for duplicates, and averages their ratios

int listIntegrity(List l);
int sortedWord(char *name1, char *name2);
