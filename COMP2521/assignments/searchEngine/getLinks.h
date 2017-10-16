#include "params.h"

typedef struct webpage{
    char *name;    
    int n_outlinks;
    char** outlinks;

    /*
    int n_inlinks;
    char** inlinks;
    */
    
    int n_words;
    char *words;

    double pageRank;
    double p_pageRank;
}Webpage;


typedef struct outputListNode{
    struct webpage *page;
    struct outputListNode *next;
}OutputListNode;

typedef struct outputListRep{
    struct outputListNode *first;
    struct outputListNode *last;
}OutputList;

int parseCollection(char *filename, char urls[MAX_URLS][20]);
Webpage newPage(char *url, int nurls);
int getOutgoingLinks(char *url, char **links);
void printPageDetails(Webpage page);

