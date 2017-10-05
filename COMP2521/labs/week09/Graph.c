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

    // trivial case
    if(src == dest){
        path[0] = src;
        return 1;
    }

    // takes the adjacency matrix from the graph
    int **adjM = g->edges;

    // for each node we visit we store its predecessor
    int *predecessors = malloc(sizeof(int) * g->nV);
    int i;

    // default is -1 that means if we haven't visited a node it will be -1
    // -1 is not a valid index so it can never be a valid path
    for(i = 0; i < g->nV; i++){
        predecessors[i] = -1;
    } 

    // we find the distance from the src to every other city 
    // this information is held in the row corresponding to that cities number
    // of the adjacency matrix
    int currCity = src;
    int *currDistances = adjM[currCity];

    // we create a flag to determine if a valid path was ever found
    int arrived = 0;

    // using a Queue as our tovisit list creates a BFS
    // since we are worried only about the number of hops, BFS always finds
    // a shortest path as the first path it finds
    Queue toVisit = newQueue();

    // loop until break from within or we reach the destination
    while(!arrived){
        int i;
        for(i = 0; i < g->nV; i ++){
            // ignore branches to themselves or ones that are too long
            if(currDistances[i] > max || i == currCity) {
                continue;
            }else{ // in here all paths are valid

                // if its predecessors is -1 that means we havent visited it yet
                // since we are performing BFS that means the fact that we have 
                // reached it now is the most efficient way to do so
                // Therefore, update the predecessor value, if we have reached
                // it before, the value will not be -1 and that means there 
                // was a shorter path to get there.
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

        // either we found a path or explored all possible paths
        if(arrived || QueueIsEmpty(toVisit)) {
            break;
        }else{ // explore the next node in the Queue (BFS)
            currCity = QueueLeave(toVisit);
            currDistances = adjM[currCity];
        }
    }


    // at this point we have all our predecessors set
    // we simply backtrack and copy the nodes into the path array

    if(arrived){
        int hops = 1;
        path[0] = dest;

        while(currCity != src){
            path[hops] = currCity;
            currCity = predecessors[currCity];
            hops++;
        }
        path[hops] = src;


        //reverse the array because of stuff
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

        // arrays start at 0
        return hops + 1;
    }else{
        return 0;
    }
}
