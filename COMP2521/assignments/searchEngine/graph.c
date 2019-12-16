#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "params.h"

Graph newGraph(int n)
{
    Graph nGraph;
    nGraph.nedges = 0;
    nGraph.nvertices = n;
    nGraph.edges = malloc(sizeof(int *) * n);
    for(int i = 0; i < n; i ++){
        nGraph.edges[i] = malloc(sizeof(int) * n);
    } 

    for(int i = 0; i < n; i ++){
        for(int j = 0; j < n; j ++){
           nGraph.edges[i][j] = 0; 
        }
    }
    
    return nGraph;

}

int getIndex(char *name, char urls[MAX_URLS][20])
{
    for(int i = 0; i < MAX_URLS; i++){
        if(strcmp(urls[i], name) == 0) return i;
    }
    return -1;
}


void addLink(Graph *g, char *source, char *destination, char urls[MAX_URLS][20])
{
    int src_index = getIndex(source, urls);
    int dest_index = getIndex(destination, urls);
    
    g->edges[dest_index][src_index] = 1;
      
    return; 
}
