#include <stdio.h>
#include "set.h"

int main (int argc, char *argv[]){
    int rankTotal = 0; //total amount of urls that have been ranked in the files
     //rank of urls in their individual files

    int unionSize = 0;
    
    char urls[MAX_URLS][20];

 //   List *rankLists = malloc((argc)*sizeof(List));

    Set fileUnion = newSet();


//makes set of all urls
    for(int fileCounter = 1; fileCounter<argc; fileCounter++){
        int indivRank = 0; 
        FILE *fin = fopen(argv[fileCounter], "r"); 
//        rankLists[fileCounter-1] = newRatioList();   
        while (fgets(urls[rankTotal], 20, fin)!=NULL){     
            indivRank++;          
            insertInto(fileUnion, urls[rankTotal]);   
          //  addList(rankLists[fileCounter-1], urls[rankTotal]);  
            rankTotal++;       
        } 
    //    calculateRatio(rankLists[fileCounter-1], indivRank);  
    }
    
    unionSize = nElems(fileUnion);
    
    Vertex *table = malloc(unionSize*sizeof(Vertex));
    
