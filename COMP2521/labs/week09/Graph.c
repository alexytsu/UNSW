// Graph.c ... implementation of Graph ADT
// Written by John Shepherd, May 2013

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "Graph.h"
#include "Queue.h"
#include <unistd.h>

// graph representation (adjacency matrix)
typedef struct GraphRep {
	int    nV;    // #vertices
	int    nE;    // #edges
	int  **edges; // matrix of weights (0 == no edge)
} GraphRep;

// check validity of Vertex
int validV(Graph g, Vertex v)
{
	return (g != NULL && v >= 0 && v < g->nV);
}

// make an edge
Edge mkEdge(Graph g, Vertex v, Vertex w)
{
	assert(g != NULL && validV(g,v) && validV(g,w));
	Edge new = {v,w}; // struct assignment
	return new;
}

// insert an Edge
// - sets (v,w) and (w,v)
void insertEdge(Graph g, Vertex v, Vertex w, int wt)
{
	assert(g != NULL && validV(g,v) && validV(g,w));
	if (g->edges[v][w] == 0) {
		g->edges[v][w] = wt;
		g->edges[w][v] = wt;
		g->nE++;
	}
}

// remove an Edge
// - unsets (v,w) and (w,v)
void removeEdge(Graph g, Vertex v, Vertex w)
{
	assert(g != NULL && validV(g,v) && validV(g,w));
	if (g->edges[v][w] != 0) {
		g->edges[v][w] = 0;
		g->edges[w][v] = 0;
		g->nE--;
	}
}

// create an empty graph
Graph newGraph(int nV)
{
	assert(nV > 0);
	int v, w;
	Graph new = malloc(sizeof(GraphRep));
	assert(new != 0);
	new->nV = nV; new->nE = 0;
	new->edges = malloc(nV*sizeof(int *));
	assert(new->edges != 0);
	for (v = 0; v < nV; v++) {
		new->edges[v] = malloc(nV*sizeof(int));
		assert(new->edges[v] != 0);
		for (w = 0; w < nV; w++)
			new->edges[v][w] = 0;
	}
	return new;
}

// free memory associated with graph
void dropGraph(Graph g)
{
	assert(g != NULL);
	// not needed for this lab
}

// display graph, using names for vertices
void showGraph(Graph g, char **names)
{
	assert(g != NULL);
	printf("#vertices=%d, #edges=%d\n\n",g->nV,g->nE);
	int v, w;
	for (v = 0; v < g->nV; v++) {
		printf("%d %s\n",v,names[v]);
		for (w = 0; w < g->nV; w++) {
			if (g->edges[v][w]) {
				printf("\t%s (%d)\n",names[w],g->edges[v][w]);
			}
		}
		printf("\n");
	}
}

// find a path between two vertices using breadth-first traversal
// only allow edges whose weight is less than "max"
int findPath(Graph g, Vertex src, Vertex dest, int max, int *path)
{

    if(src == dest){
        path[0] = src;
        return 1;
    }

    int **adjM = g->edges;

    int *predecessors = malloc(sizeof(int) * g->nV);
    int aids;
    for(aids = 0; aids < g->nV; aids++){
        predecessors[aids] = -1;
    } 

    int currCity = src;
    int *currDistances = adjM[currCity];

    int arrived = 0;

    Queue toVisit = newQueue();

    while(!arrived){
        int i = 0;
        for(i = 0; i < g->nV; i ++){
            if(currDistances[i] > max || i == currCity) {
                continue;
            }else{ // in here all paths are valid
                if(predecessors[i] == -1){
                    predecessors[i] = currCity;
                    QueueJoin(toVisit, i);
                    if(i == dest){
                        arrived = 1;
                        break;
                    }
                }
            }
        }


        if(arrived || QueueIsEmpty(toVisit)) {
            break;
        }else{
            currCity = QueueLeave(toVisit);
            currDistances = adjM[currCity];
        }
        

    }
    if(arrived){
        int hops = 1;
        path[0] = dest;

        while(currCity != src){
            path[hops] = currCity;
            currCity = predecessors[currCity];
            hops++;
        }
        path[hops] = src;

        int i = hops;
        int j = 0; 
        while(i > j)
        {
            int temp = path[i];
            path[i] = path[j];
            path[j] = temp;
            i--;
            j++;
        }


        
        return hops + 1;
    }else{
        return 0;
    }


}
