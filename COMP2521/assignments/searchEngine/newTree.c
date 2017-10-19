#include <stdio.h>
#include "bstree.h"
#include "params.h"

typedef struct treeNode{
	char *url;
	double tfidf;
	int deleted;
	struct node *left;
	struct node *right;
}TreeRep;

typedef TreeRep *Tree;

Tree newTreeNode(char *name, double tfidf)
{
	Tree new = malloc(sizeof(TreeRep));
	new->left = new->right = NULL;
	new->deleted = 0;
	new->tfidf = tfidf;
	strcpy(new->url, name);
	return new;
}

Tree insertNode(Tree root, Tree insert)
{
	if(root == NULL) return insert;
	else if(insert->tfidf < root->tfidf){
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

void printFromLargest(Tree root)
{
	if(page->right != NULL) printFromLargest(page->
}
