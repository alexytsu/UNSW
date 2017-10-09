#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "getLinks.h"


void printPageDetails(Webpage page)
{
    printf("=====PRINTING PAGE DETAILS=====\n");
    printf("Page Name:\t %s\n", page.name);
    printf("Out Degrees:\t %d\n", page.n_outlinks);
    printf("PageRank:\t %.7f\n", page.pageRank);	  
    if(page.n_outlinks > 0){
        printf("\nOutgoing Links: \n");
        int i = 0;
        for(i = 0; i < page.n_outlinks; i ++){
            printf("\t%s\n", page.outlinks[i]);
        }
    }
    printf("\n");
}

Webpage newPage(char *url, int nurls)
{
    Webpage newPage;
    
    newPage.name = malloc(sizeof(char) * 20);
    strcpy(newPage.name, url);  

    newPage.outlinks = malloc(sizeof(char *) * nurls);
    //newPage.outIDs = malloc(sizeof(PageID) * nurls);
    
    int i;
    for(i = 0; i < nurls; i++){
        newPage.outlinks[i] = malloc(sizeof(char) * 20);
        //newPage.outIDs[i].name = malloc(sizeof(char) * 20);
    }
    //newPage.n_outIDs = getOutgoingIDs(url, newPage.outIDs);
    newPage.n_outlinks = getOutgoingLinks(url, newPage.outlinks);
    
    newPage.pageRank = 1/nurls;

    return newPage;
}

int parseCollection(char *filename, char urls[MAX_URLS][20])
{
    FILE *fin = fopen(filename, "r");
    int i = 0; 
    while(fscanf(fin, "%s", urls[i]) != -1){
        i++;
    }
    return i;
}

int getOutgoingLinks(char *url, char **links)
{
    char filename[30];

    strcpy(filename, "Sample1/");
    strcat(filename, url);
    strcat(filename, ".txt");

    FILE *fin = fopen(filename, "r");

    char buffer[1000];
    int n_outlinks = 0;
    char outlink[20];
    fgets(buffer, 1000, fin);
    
    assert(strcmp(buffer, "#start Section-1\n")==0);    
    while(fscanf(fin, "%s", outlink) != -1){
        if(strcmp(outlink, "#end") == 0) break;
        strcpy(links[n_outlinks], outlink);
        n_outlinks++;
    } 
 
    return n_outlinks;
}
