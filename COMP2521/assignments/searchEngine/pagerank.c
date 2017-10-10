#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "getLinks.h"
#include "graph.h"
#include "params.h"

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

    Graph linkMatrix = newGraph(nurls);
    
    for(i = 0; i < nurls; i ++){
        //pages[i] corresponds to  the page where we have the outlinks
        Webpage currPage = pages[i];
        for(int j = 0; j < currPage.n_outlinks; j++){
            addLink(&linkMatrix, currPage.name, currPage.outlinks[j], urls);
        }
    }

    for(int i = 0; i < linkMatrix.nvertices; i++){
        for(int j = 0; j < linkMatrix.nvertices; j++){
            printf("%d", linkMatrix.edges[j][i]);
        }
        printf("\n");
    }

    int iteration = 0;
    double damping = 0.85;

    while(iteration < 10000){
        iteration ++;
        for(i = 0; i < nurls; i ++){

            int nincoming = 0;

            for(int j = 0; j < linkMatrix.nvertices; j++){
                nincoming += linkMatrix.edges[i][j]; //i and j direction?
            }

            int *referenced_inlinks = malloc(sizeof(int) * nincoming);
            int *referenced_outlinks = malloc(sizeof(int) * nincoming);
            double *incoming_pagerank = malloc(sizeof(double) * nincoming);

            int referenced_inlinks_sum = 0;
            int referenced_outlinks_sum = 0;

            int counter = 0;
            for(int j = 0; j < linkMatrix.nvertices; j ++){
                if(linkMatrix.edges[i][j]){
                    int pageInlinks = 0;
                    for(int k = 0; k < linkMatrix.nvertices; k ++){
                        pageInlinks += linkMatrix.edges[j][k];
                    }
                    incoming_pagerank[counter] = pages[j].pageRank;
                    referenced_inlinks[counter] = pageInlinks;
                    referenced_inlinks_sum += pageInlinks;
                    referenced_outlinks[counter] = pages[j].n_outlinks;
                    referenced_outlinks_sum += pages[j].n_outlinks;
                    counter ++;
                } 
            }
            double secondpart = 0;
            for(int j = 0; j < nincoming; j++){
                secondpart += incoming_pagerank[j] * referenced_outlinks[j]/(double)referenced_outlinks_sum * referenced_inlinks[j]/(double)referenced_inlinks_sum;
            }

            
            pages[i].pageRank = (1-damping)/nurls + damping * secondpart;
        }
        
    }

    for(int i = 0; i < nurls; i++){
        printPageDetails(pages[i]);
    }

    double pageRankTotal = 0;
    for(int i = 0; i < nurls; i++){
        pageRankTotal += pages[i].pageRank;
    }

    printf("==== PAGERANK TOTAL: %.7f\n", pageRankTotal);
    
}


