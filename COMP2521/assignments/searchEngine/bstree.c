#include <stdio.h>
#include "bstree.h"
#include "params.h"

//!! make case for if tfidf are equal


typedef struct node{
//stores either frequency or page
    char *Page;
    double num;
    int deleted;
    struct node *left;
    struct node *right;    
}tree;

tree newTree(double val){
    tree new = malloc(sizeof(struct node));
    assert(new);
    new->Page=NULL;
    new->num = val;
    new->left=new->right=NULL;
    new->deleted=0;
    return new;
}



//this will probs be very broken
void insertPage(tree t, char *url, int tfidf){
    tree new = newTree(url);
    new->Page = malloc(PNEUMONOULTRAMICROSCOPICSILICOVOLCANOCONIOSIS*sizeof(char *));
    strcpy(new->Page, url);
        
    new->tfidf = tfidf;
    /*if(t->root==NULL){
        t->root=new;
    }
    */
    tree n = insertPageNode(t, new);
}

tree insertPageNode(tree root, tree insert){
    
    if(root==NULL) return insert;
    else if(insert->num<root->num){
        root->left = insertPageNode(root->left, insert);
    }
    else if(insert->num>root->num){
        root->right = insertPageNode(root->right, insert);
    }
    return root;
    
}
void deleteNode(tree n){
    n->deleted=1;
}

int empty(Tree t){
    assert(t!=NULL);
    if (t->root==NULL) return 1;
    return 0;
}

void printFromLargest(tree page){
    if(page->right!=NULL) printFromLargest(page->right);
    printf("%s %.6lf\n",page->Page, page->num);
    deleteNode(page);
    if(page->left!=NULL) printFromLargest(page->left);
    
}

