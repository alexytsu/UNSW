#include <stdio.h>
#include <stdlib.h>
#include "params.h"
#include "set.h"
int main (int argc, char *argv[]){
    int rankTotal = 0; //total amount of urls that have been ranked in the files
    int indivRank = 0;  //rank of urls in their individual files

    int unionSize = 0;
    double sizeRatio = 0;
    
    char urls[MAX_URLS][20];

    //tree for each file (argc), nodes store url and its respective size ratio indivRank/
    Lists rankLists = malloc((argc)*sizeof(List));

    //union of urls from all specified rank files
    Set fileUnion= newSet();

    //keeps track of each rank file from command arg
    for(int fileCounter = 1; fileCounter<argc; fileCounter++){
        FILE *fin = fopen("argv[%d]", "r", fileCounter);  //for each file
        rankLists[fileCounter-1] = newList();   //make a new list for that file
        indivRank = 0;  //start counting how many ranks there are
        while (fgets(urls[rankTotal], 20, fin)!=NULL){      //reads each line/rank of file into urls[]         
            indivRank++;          //counts total ranks in specific file, also functions as set size for the rank file
            insertInto(fileUnion, urls[rankTotal]);     //inserts url read into a union
            !!!!addList(rankLists[fileCounter-1], urls[rankTotal]);   //inserts url read into list of urls from that file
            ranktotal++;        //increments 
        } 
        !!!! calculateRatio(rankLists[fileCounter], indivRank);      
        
    }
    
    
    unionSize = nElems(fileUnion);
    for(int fileCounter = 1; fileCounter<argc; fileCounter++){
        !!!! combineLists(rankLists[0], rankLists[fileCounter]);    //combines urls read from all files with duplicates, in no particular order
    }    
    
    List findRank = newList();

    !!!!copyList(findRank, rankLists[0]);   //copies all urls from rankLists->findRank in alphabetical order
    !!!!computeAvgRatio(findRank);  //combines url duplicates and averages their ratio
    Tree urlsByRatio = !!!!makeTree(findRank);  //makes a tree out of the list, sorted by ratio size

    printAscending(urlsByRatio);    //prints tree from highest to lowest rank

    return 0;
}
