#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "getLinks.h"
#include "graph.h"
#include "params.h"
double w_out(char *v, char*u, Graph linkMatrix, char urls[MAX_URLS][20], Webpage *pages);
double w_in(char* v, char* u, Graph linkMatrix, char urls[MAX_URLS][20], Webpage *pages);
int main(int argc, char *argv[])	
{

    //Get urls from collection.txt
    char urls[MAX_URLS][20];
    int nurls;
    printf("Number of pages: %d\n", nurls = parseCollection("Sample1/collection.txt", urls));
    
    printf("====================== Initializing Pages ======================\n");
    //Create an array of all pages
    Webpage *pages = malloc(sizeof(Webpage) * nurls);
    int i = 0;
    for(i = 0; i < nurls; i++){
        printf("Creating a webpage for %s\n", urls[i]);
        pages[i] = newPage(urls[i], nurls);
    }   

    Graph linkMatrix = newGraph(nurls);

    for(i = 0; i < nurls; i ++){
        //pages[i] corresponds to  the page where we have the outlinks
        Webpage currPage = pages[i];
        for(int j = 0; j < currPage.n_outlinks; j++){
            addLink(&linkMatrix, currPage.name, currPage.outlinks[j], urls);
        }
    }

    printf("\n=================== GRAPH ADJACENCY MATRIX ======================\n");
    for(int i = 0; i < linkMatrix.nvertices; i++){
        for(int j = 0; j < linkMatrix.nvertices; j++){
            printf("%d", linkMatrix.edges[i][j]);
        }
        printf("\n");
    }

    double damping = 0;
    int maxIterations = 0;
    double diffPR = 0;

    if(argc == 1){
        damping = 0.85;
        diffPR = 0.0001;
        maxIterations = 1000; 
        printf("DEFAULT VALUES USED\n");
    } else if(argc == 4){
        damping = atof(argv[1]);
        diffPR = atof(argv[2]);
        maxIterations = atoi(argv[3]);
    }else{
        fprintf(stderr, "Incorrect number of arguments supplied\n");
        fprintf(stderr, "USAGE: ./pagerank [damping] [diffPR] [maxIterations]\n");
        exit(1);
    }

    double diff = diffPR;
    double lastTotalPageRank = 1;

    int timesRan = 0;

    for(int i = 0; i < maxIterations && diff >= diffPR; i++){

        for(int j = 0; j < nurls; j++){

            char *currentUrl = urls[j];
            double sum_right = 0.0;

            for(int k = 0; k < linkMatrix.nvertices; k++){
                if(linkMatrix.edges[j][k]){
                    sum_right += pages[k].pageRank * w_in(urls[k], currentUrl, linkMatrix, urls, pages) * w_out(urls[k], currentUrl, linkMatrix, urls, pages);   
                }
            }
            pages[j].pageRank = (1-damping)/(double)nurls + damping*sum_right;
        }

        double currentTotal =  0;
        for(int l = 0; l < nurls; l++){
            currentTotal += pages[i].pageRank;
        }   


        diff = lastTotalPageRank - currentTotal;
        diff = (diff < 0) ? -diff:diff;
        printf("iteration %d: %.7f\n", i+1, diff);
        lastTotalPageRank = currentTotal;

        timesRan = i;
    }

    printf("Times Ran: %d\n", timesRan+1);

    /*
       printf("We want to list all links coming into url11\n");
       int index11 = getIndex("url11", urls);
       for(int i = 0; i < linkMatrix.nvertices; i ++){
       printf("%d",linkMatrix.edges[index11][i]);
       }
       */

    double totalPagerank = 0;
    for(int i = 0; i < nurls; i++){
        printPageDetails(pages[i]);
        totalPagerank += pages[i].pageRank;
    }   

    PageAndRank *outputList = malloc(sizeof(PageAndRank) * nurls);    
    for(int i = 0; i < nurls; i++){
        outputList[i].name = malloc(sizeof(char) * 20);
    }

    for(int i = 0; i < nurls; i++){
        printf("%d\n", i);
        printf("%s: %.7lf\n", urls[i], pages[i].pageRank);
        strcpy(outputList[i].name, urls[i]);
        outputList[i].pageRank = pages[i].pageRank;
    }



    printf("\n\n\n TOTAL PAGERANK: %.7lf\n", totalPagerank);

}


double w_in(char* v, char* u, Graph linkMatrix, char urls[MAX_URLS][20], Webpage *pages)
{

    double win = 0;
    //url11 -> url31

    int source = getIndex(v, urls);
    int dest = getIndex(u, urls);

    int destIncoming = 0;
    for(int i = 0; i < linkMatrix.nvertices; i ++){
        destIncoming += linkMatrix.edges[dest][i];
    }

    int sumOfInlinksOfPagesThatSourcePointsTo = 0; 
    for(int i = 0; i <  pages[source].n_outlinks; i ++){
        int pageThatSourcePointsTo = getIndex(pages[source].outlinks[i], urls); 
        for(int j = 0; j < linkMatrix.nvertices; j++){
            sumOfInlinksOfPagesThatSourcePointsTo += linkMatrix.edges[pageThatSourcePointsTo][j];
        }
    }

    win = (double) destIncoming/ (double) sumOfInlinksOfPagesThatSourcePointsTo;
    return win;
}

double w_out(char *v, char*u, Graph linkMatrix, char urls[MAX_URLS][20], Webpage *pages)
{ 
    double wout = 0.0;

    int source = getIndex(v, urls);
    int dest = getIndex(u, urls);

    int destOutgoing = pages[dest].n_outlinks;

    double sumOfOutlinksOfPagesThatSourcePointsTo = 0; 
    for(int i = 0; i <  pages[source].n_outlinks; i ++){
        int pageThatSourcePointsTo = getIndex(pages[source].outlinks[i], urls); 
        sumOfOutlinksOfPagesThatSourcePointsTo += (pages[pageThatSourcePointsTo].n_outlinks == 0) ? 0.5:pages[pageThatSourcePointsTo].n_outlinks;
    }

    wout = (double)destOutgoing/(double)sumOfOutlinksOfPagesThatSourcePointsTo;
    return wout;



}

