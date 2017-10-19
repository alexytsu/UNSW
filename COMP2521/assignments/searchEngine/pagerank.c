#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "getLinks.h"
#include "graph.h"
#include "params.h"

double w_out(char *v, char*u, Graph linkMatrix, char urls[MAX_URLS][20], Webpage *pages);
double w_in(char* v, char* u, Graph linkMatrix, char urls[MAX_URLS][20], Webpage *pages);
void insertOrdered(OutputList *L, Webpage *page);
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
        diffPR = 0.000001;
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

    int timesRan = 0;

    for(int i = 0; i < maxIterations && diff >= diffPR; i++){

        for(int j = 0; j < nurls; j++){

            char *currentUrl = urls[j];
            double sum_right = 0.0;
            for(int k = 0; k < linkMatrix.nvertices; k++){
                if(linkMatrix.edges[j][k]){
            if(i == 0){
            printf("Comparison between %s & %s:\n", urls[j], urls[k]);
            printf("\t win: %.7lf\n", w_in(urls[k], currentUrl, linkMatrix, urls, pages));
            printf("\t wout: %.7lf\n", w_out(urls[k], currentUrl, linkMatrix, urls, pages));
            }
                    sum_right += pages[k].pageRank * w_in(urls[k], currentUrl, linkMatrix, urls, pages) * w_out(urls[k], currentUrl, linkMatrix, urls, pages);   
                }
            }
            pages[j].p_pageRank = pages[j].pageRank;
            pages[j].pageRank = (double)(1-damping)/(double)nurls + damping*sum_right;
        }

        diff = 0;
        for(int j = 0; j < nurls; j ++){
            double new = pages[j].pageRank - pages[j].p_pageRank;
            diff = (diff < 0) ? -diff:diff;
            diff += new;
        }

        diff = (diff < 0) ? -diff:diff;
        printf("iteration %d: %.7f\n", i+1, diff);

        timesRan = i;
    }

    printf("\n=========================\n");
    printf("Times Ran: %d\n", timesRan+1);

    OutputList * outputL;
    outputL = malloc(sizeof(OutputList *));
    outputL->first = malloc(sizeof(Webpage *));
    outputL->last = malloc(sizeof(Webpage *));
    outputL->first = NULL;
    outputL->last = NULL;


    FILE *fout = fopen("pagerankList.txt", "w");

    for(int i = 0; i < nurls; i++){
        printf("Ran %d times\n", i);
        insertOrdered(outputL, &pages[i]);
    }

    for(OutputListNode *curr = outputL->first;curr!=NULL;curr=curr->next){
        printf("%s, %d, %.7lf\n", curr->page->name, curr->page->n_outlinks, curr->page->pageRank);
        fprintf(fout, "%s, %d, %.7lf\n", curr->page->name, curr->page->n_outlinks, curr->page->pageRank);
    }

    fclose(fout);
}


OutputListNode *newNode(Webpage *page){
    OutputListNode *new = malloc(sizeof(OutputListNode *));
    new->page = page;
    new->next = NULL;
    return new;
}

void insertOrdered(OutputList *L, Webpage *page)
{
    OutputListNode *n = newNode(page);
    printf("%p\n", L);
    OutputListNode *curr = L->first;
    OutputListNode *prev = NULL;

    if(curr == NULL){
        printf("HI\n");
        L->first = L->last = n;
        return;
    }

    while(curr!=NULL && page->pageRank < curr->page->pageRank){
        prev = curr;
        curr = curr->next;
    }

    if(prev == NULL){
        L->first = n;
        n->next = curr;
    }else{
        prev->next = n;
        n->next = curr;
        if(n->next == NULL){
            L->last = n;
        }
    }
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

    double sumOfInlinksOfPagesThatSourcePointsTo = 0; 
    for(int i = 0; i <  pages[source].n_outlinks; i ++){
        int pageThatSourcePointsTo = getIndex(pages[source].outlinks[i], urls); 
        for(int j = 0; j < linkMatrix.nvertices; j++){
            sumOfInlinksOfPagesThatSourcePointsTo += linkMatrix.edges[pageThatSourcePointsTo][j];
        }
    }

    win = (double) destIncoming/ (double) sumOfInlinksOfPagesThatSourcePointsTo;
    return win;
}

double w_out(char *v, char *u, Graph linkMatrix, char urls[MAX_URLS][20], Webpage *pages)
{ 
    double wout = 0.0;

    int source = getIndex(v, urls);
    int dest = getIndex(u, urls);

    double destOutgoing = (pages[dest].n_outlinks == 0) ? 0.5:pages[dest].n_outlinks;

    double sumOfOutlinksOfPagesThatSourcePointsTo = 0; 
    for(int i = 0; i <  pages[source].n_outlinks; i ++){
        int pageThatSourcePointsTo = getIndex(pages[source].outlinks[i], urls); 
        sumOfOutlinksOfPagesThatSourcePointsTo += (pages[pageThatSourcePointsTo].n_outlinks == 0) ? 0.5:pages[pageThatSourcePointsTo].n_outlinks;
    }

    wout = (double)destOutgoing/(double)sumOfOutlinksOfPagesThatSourcePointsTo;
    return wout;
}

