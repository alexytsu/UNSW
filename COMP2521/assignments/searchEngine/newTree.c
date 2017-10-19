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
    printf("%s: %d [%s] [%s]\n", root->url, root->matches, (root->right == NULL)? "X":root->right->url,(root->left == NULL)? "X":root->left->url);
    if(root->left != NULL) printTree(root->left);
    if(root->right != NULL) printTree(root->right);
}

Tree insertNodeWithValues(Tree root, double tfidf, int matches, char *name)
{
    if(root == NULL)
        return newTreeNode(name, tfidf, matches);
    else if (tfidf < root->tfidf)
        root->left = insertNodeWithValues(root->left, tfidf, matches, name);
    else if (tfidf > root->tfidf)
        root->right = insertNodeWithValues(root->right, tfidf, matches, name);
    return root;
}

Tree insertNode(Tree root, Tree insert)
{
	if(root == NULL) return insert;
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
    if(t == NULL) return 1;
    else return 0;
    int left = empty(t->left);
    int right = empty(t->right);
    if(left == 1 && right == 1){
        return 1;
    }
    return 0; 
}

void printFromLargest(Tree root)
{
    static int printed = 0;
    if(printed >= 30) return;
    if(root == NULL) return;
    if(root->right != NULL) printFromLargest(root->right);
    //printf("%d: %s: %.6lf\n", printed, root->url, root->tfidf);

    printed++;
    if(root->left!=NULL) printFromLargest(root->left);
}
