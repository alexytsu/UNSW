#include <stdio.h>

/*------------------------------------------------------------------------------
 * Determine whether a graph G contains a universal sink - a vertex with
 * in-degree v-1 and out-degree 0 - in time O(v), given an adjacency matrix
 * for G.
 * ---------------------------------------------------------------------------*/

int universalSink(int elems, int adjM[elems][elems])
{


}


int main(void)
{
   int adjM1[4][4] = {{0,0,1,0},{0,0,1,0},{0,0,0,0},{0,0,1,0}}; 
   int adjM2[4][4] = {{0,0,1,0},{0,0,0,0},{0,0,0,0},{0,0,1,0}}; 
   printf("%d\n", universalSink(4, adjM1));
   printf("%d\n", universalSink(4, adjM2));
}
