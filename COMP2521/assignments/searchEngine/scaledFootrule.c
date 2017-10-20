#include <stdio.h>
#include <stdlib.h>
#include "params.h"
#include "ratioList.h"
#include "newTree.h"
#include "linkedList.h"
#include "set.h"

int main (int argc, char *argv[]){
    int rankTotal = 0; //total amount of urls that have been ranked in the files
    int indivRank = 0;  //rank of urls in their individual files

//    int unionSize = 0;
    
    char urls[MAX_URLS][20];

    //tree for each file (argc), nodes store url and its respective size ratio indivRank/
    List *rankLists = malloc((argc)*sizeof(List));

    //union of urls from all specified rank files
    Set fileUnion= newSet();

    //keeps track of each rank file from command arg
    for(int fileCounter = 1; fileCounter<argc; fileCounter++){
        FILE *fin = fopen("argv[%d]", "r");  //for each file
        rankLists[fileCounter-1] = newRatioList();   //make a new list for that file
        indivRank = 0;  //start counting how many ranks there are
        while (fgets(urls[rankTotal], 20, fin)!=NULL){      //reads each line/rank of file into urls[]         
            indivRank++;          //counts total ranks in specific file, also functions as set size for the rank file
            insertInto(fileUnion, urls[rankTotal]);     //inserts url read into a union
            addList(rankLists[fileCounter-1], urls[rankTotal]);   //inserts url read into list of urls from that file
            rankTotal++;        //increments 
        } 
        calculateRatio(rankLists[fileCounter], indivRank);    //assigns a ratio to each url in rankLists respective to their individual rank in that list
        
    }
    
    
//    unionSize = nElems(fileUnion);  //find total amount of urls that are to be ranked, no duplicates
    for(int fileCounter = 1; fileCounter<argc; fileCounter++){
        combineLists(rankLists[0], rankLists[fileCounter]);    //combines urls read from all files with duplicates, in no particular order
    }    
    
    List findRank = newRatioList();

    copyList(findRank, rankLists[0]);   //copies all urls from rankLists->findRank in alphabetical order
    computeAvgRatio(findRank);  //combines url duplicates and averages their ratio
    Tree urlsByRatio = makeTree(findRank);  //makes a tree out of the list, sorted by ratio size

    printAscending(urlsByRatio);    //prints tree from highest to lowest rank

    return 0;
}
