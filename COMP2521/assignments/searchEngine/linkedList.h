#include <stdio.h>
#include "params.h"

typedef struct node *Node;
typedef struct listRep *List;

List newList();
void insertWord(List l, char *w);
Node newNode(char *c);
Node fromList(List l);
void insertUrl(List l, char *w, char urls[MAX_URLS]);
int sortedWord(char *name1, char *name2);
int noUrls(List l, char *word);
int listIntegrity(List l);
void showList(List l);
void filterList(List l);
void removeNext(List l, Node keep);
void printIndex(List l, FILE *fout);
