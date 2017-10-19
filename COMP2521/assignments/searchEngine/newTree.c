#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "newTree.h"
#include "params.h"

Tree newTreeNode(char *name, double tfidf, int matches)
{
	Tree new = malloc(sizeof(TreeRep));
	new->left = new->right = NULL;
	new->deleted = 0;
    new->matches = matches;
	new->tfidf = tfidf;
    new->url = malloc(sizeof(char) * PNEUMONOULTRAMICROSCOPICSILICOVOLCANOCONIOSIS);
	strcpy(new->url, name);
	return new;
}

void printTree(Tree root)
{
    if(root == NULL) return;
    if(root->left != NULL) printTree(root->left);
    printf("%s: %d\n", root->url, root->matches);
    if(root->right != NULL) printTree(root->right);
}

Tree insertNode(Tree root, Tree insert)
{
    printf("Printing tree\n");
    printTree(root);
    printf("Printing node\n");
    printTree(insert);

	if(root == NULL) return insert;
 
    if(insert->matches < root->matches){
        root->left = insertNode(root->left, insert);
    }else if(insert->matches > root->matches){
        root->right = insertNode(root->left, insert);
    }

    printf("Same number of matches\n");
    
    if(insert->tfidf < root->tfidf){
		root->left = insertNode(root->left, insert);
	}else if(insert->tfidf > root->tfidf){
		root->right = insertNode(root->right, insert);
	}
	return root;
}

void deleteNode(Tree t)
{
	t->deleted = 1;
}

int empty(Tree t)
{
    if(t->deleted == 0){
        return 0;
    }
    if(t == NULL) return 1;

    int left = empty(t->left);
    int right = empty(t-right);

    if(left == 1 && right == 1){
        return 1;
    }
    return 0; 
}

void printFromLargest(Tree root)
{
    if(root->right != NULL) printFromLargest(root->right);
    printf("%s: %.6lf\n", root->url, root->tfidf);
    deleteNode(root);
    if(root->left!=NULL) printFromLargest(root->left);
}
