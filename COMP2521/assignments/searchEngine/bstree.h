#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
typedef struct node *Tree; 
 
Tree newTree();
Node newNode(char *val);

//inserts nodes for frequency and page trees
void insertPage(Tree t, char *url, int tfidf);
Node insertPageNode(Node root, Node insert);
//void checkRepeat(); shouldnt be necessary
void printFromLargest(Tree t);
void deleteNode(Node n);
int empty(Tree t);  //returns 1 if tree is empty
    
    
    
    
    
    
    
    
    

