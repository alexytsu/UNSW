#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <string.h>
#include "setRank.h"
#include "ratioList.h"
#include "perms.h"
#include "params.h"

int main(int argc, char *argv[]){
    int numberOfFiles = argc;   //not argc-1 because going to implement counters starting at 1
    int fileCounter = 1;
    double scaledFootRank = 0;
    char urls[MAX_URLS][20];
    int unionSize = 0;
    int rankTotal = 0;

    
    List *fileLists = malloc((argc)*sizeof(List));  //contains urls from each file
    Set fileUnion = newSetRank();

    int fileSize;  //amount of urls in each respective file

    while (fileCounter<=numberOfFiles){
            fileSize = 0;
            FILE *fin = fopen(argv[fileCounter], "r");  //for each file

            fileLists[fileCounter-1] = newRatioList();   //make a new list for that file, counter-1 because array should start at 0

            while (fgets(urls[rankTotal], 20, fin)!=NULL){      //reads each line/rank of file into urls[]         
                fileSize++;          //counts total ranks in specific file, also functions as set size for the rank file
printf("sigh\n");
                //Set
                insertIntoRank(fileUnion, urls[rankTotal]);     //inserts url read into a union
                //Linked List
                addRatioList(fileLists[fileCounter-1], urls[rankTotal], 0);   //inserts url read into list of urls from that file
                rankTotal++;        //increments 
            }
            calculateRatio(fileLists[fileCounter-1], fileSize);    //assigns a ratio to each url in fileListss respective to their individual rank in that list
            fileCounter++;
    printf("sigh\n");
    }
    List allUrls = newRatioList();
    for(int listCounter=0; listCounter<numberOfFiles; listCounter++){
        combineLists(allUrls, fileLists[listCounter]);
    }

printf("sigh\n");
   
    unionSize = nElemsRank(fileUnion);
    Set ranked = newSetRank();
    int *pVector = malloc(unionSize*sizeof(int));
    for(int i=0; i<unionSize; i++){
        pVector[i] = i;
    }
    scaledFootRank = heappermute(fileUnion, &ranked, allUrls, pVector, unionSize, scaledFootRank); //calculates scaledfootrank for all permutations
    printf("%lf\n", scaledFootRank);

}

