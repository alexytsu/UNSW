#include <stdio.h>
#include "params.h"

typedef struct node *Node;
typedef struct listRep *List;

List newList();

void insertWord(List l, char *w);   //for making a list of all unique words that appear across all webpages
void insertWordsInPage(List l, char *word); //for inserting a newWordNode
Node newNode(char *c);
Node newWordNode(char *word);     //for a node for each word that appear on specific webpage
Node fromList(List l);      //returns first node in list
void insertUrl(List l, char *w, char urls[MAX_URLS]);   //inserts url node for page list in overaching word index
int sortedWord(char *name1, char *name2);   //sorts string in alphabetical order
int noUrls(List l, char *word);     //returns length of page list, unused as of yet 
int listIntegrity(List l);      //checks if list is valid
void showList(List l);      
void filterList(List l);        //filters out duplicates in list
void removeNext(List l, Node keep);     //removes node succeeding keep
void printIndex(List l, FILE *fout);    //prints contents of list to text file
int dupWordCount(List l, char *word);    //counts duplicates of a particular word in list
int find(List l, char *word);     //returns 1 if finds word in list
int length(List l);
void clearList(List l);         
