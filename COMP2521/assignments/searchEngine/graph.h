#include "params.h"

typedef struct directedAdjacencyMatrix{
    int nedges;
    int nvertices;
    int **edges;
}Graph;

Graph newGraph(int n);
void addLink(Graph *g, char *source, char *destination, char urls[MAX_URLS][20]);
int getIndex(char *name, char urls[MAX_URLS][20]);
