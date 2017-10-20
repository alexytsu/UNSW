#ifndef TREE
#define TREE
typedef struct treeNode{
	char *url;
    int matches;
	double tfidf;
	int deleted;
	struct treeNode *left;
	struct treeNode *right;
}TreeRep;

typedef TreeRep *Tree;
Tree newTreeNode(char *name, double tfidf, int matches);
Tree insertNode(Tree root, Tree insert);
Tree insertNodeWithValues(Tree root, double tfidf, int matches, char *name);
void deleteNode(Tree t);
void printFromLargest(Tree root);
void printTree(Tree root);
int empty(Tree t);
#endif
