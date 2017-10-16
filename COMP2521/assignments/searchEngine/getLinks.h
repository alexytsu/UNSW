#include "params.h"

typedef struct webpage{
    char *name;    
    int n_outlinks;
    char** outlinks;

    int n_inlinks;
    char** inlinks;
    
    double pageRank;
    double p_pageRank;
}Webpage;


typedef struct outputList{
    struct webpage *page;
    struct outputList *next;
}OutputList;

int parseCollection(char *filename, char urls[MAX_URLS][20]);
Webpage newPage(char *url, int nurls);
int getOutgoingLinks(char *url, char **links);
void printPageDetails(Webpage page);

