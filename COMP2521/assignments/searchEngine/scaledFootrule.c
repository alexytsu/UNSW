#include <stdio.h>
#include <stdlib.h>
#include "params.h"
#include "ratioList.h"
#include "newTree.h"
#include "linkedList.h"
#include "set.h"

void showRatioList(List l)
{
    for(node *curr = l->first; curr!=NULL; curr = curr->next){
        printf("%s:%.2lf\n", curr->url, curr->ratio);
    }
}

int main (int argc, char *argv[]){
    int rankTotal = 0; //total amount of urls that have been ranked in the files

    //int unionSize = 0;
    
    char urls[MAX_URLS][20];

    //tree for each file (argc), nodes store url and its respective size ratio indivRank/
    List *rankLists = malloc((argc)*sizeof(List));

    //union of urls from all specified rank files
    Set fileUnion= newSet();

    //keeps track of each rank file from command arg
    int indivRank;
    for(int fileCounter = 1; fileCounter<argc; fileCounter++){
        indivRank = 0;  //start counting how many ranks there are
        FILE *fin = fopen(argv[fileCounter], "r");  //for each file
        rankLists[fileCounter-1] = newRatioList();   //make a new list for that file

        while (fgets(urls[rankTotal], 20, fin)!=NULL){      //reads each line/rank of file into urls[]         
            indivRank++;          //counts total ranks in specific file, also functions as set size for the rank file
            //Set
            insertInto(fileUnion, urls[rankTotal]);     //inserts url read into a union
            //Linked List
            addList(rankLists[fileCounter-1], urls[rankTotal], 0);   //inserts url read into list of urls from that file
            rankTotal++;        //increments 
        } 

        calculateRatio(rankLists[fileCounter-1], indivRank);    //assigns a ratio to each url in rankLists respective to their individual rank in that list
    }
    
    for(int i = 0; i < argc-1;i++){
        printf("From file%d we have: \n",i+i);
        showRatioList(rankLists[i]);
    }
    
//    unionSize = nElems(fileUnion);  //find total amount of urls that are to be ranked, no duplicates
    for(int fileCounter = 1; fileCounter<argc-1; fileCounter++){
        combineLists(rankLists[0], rankLists[fileCounter]);    //combines urls read from all files with duplicates, in no particular order
        printf("After combining\n");
        showRatioList(rankLists[0]);
    }    
    
    showSet(fileUnion);        

    int uniqueURLs = nElems(fileUnion);    
    List unionURLS = newRatioList();
    while(nElems(fileUnion) > 0){
        addList(unionURLS, 
    }

    double **costMatrix = malloc(sizeof(int*) * uniqueURLs);
    for(int i = 0; i < uniqueURLs; i ++){
        costMatrix[i] = malloc(sizeof(int) * uniqueURLs);
    }
    
  
    
    return 0;
}

