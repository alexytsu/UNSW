#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "getLinks.h"

int main()	
{

    //Get urls from collection.txt
    char urls[MAX_URLS][20];
    int nurls;
    printf("Number of pages: %d\n", nurls = parseCollection("Sample1/collection.txt", urls));

    //Create an array of all pages
    Webpage *pages = malloc(sizeof(Webpage) * nurls);
    int i = 0;
    for(i = 0; i < nurls; i++){
        printf("Creating a webpage for %s\n", urls[i]);
        pages[i] = newPage(urls[i], nurls);
        printPageDetails(pages[i]);
    }   

    for(i = 0; i < nurls; i++){
        printf("Assigning in degrees and IDs\n");

    }

    /*Graph linkMatrix = newGraph(nurls);
    
    for(i = 0; i < nurls; i++){
        Page p = pages[i];
        int j = 0;        
        for(j = 0; j < p.n_outlinks; j ++){
            insertEdge(linkMatrix, p.name, p.outlinks[j]);
        }
    }
*/	
    int iteration = 0;
    double damping = 0.85;
    
    while(iteration < 100){
        iteration ++;
        for(i = 0; i < nurls; i ++){
            //pages[i].pageRank = (1-damping)/nurls + damping * 0.5 * 0.5;
        }
        
    }
    
}


