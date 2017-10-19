#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "graph.h"
#include "params.h"
#include "frequency.h"
#include "newTree.h"
#include "linkedList.h"
#include "neatening.h"

int main(int argc, char *argv[]){

    if(argc<2){
        fprintf(stderr, "Not enough arguments\n");
        exit(1);
    }
    
    char urls[MAX_URLS][20];
    
    int nurls = parseCollection("Sample1/collection.txt", urls);
    int n_terms = argc-1;
    int output = 0;
    int pageCounter = 0;
    int j = argc;
    
    //array of trees linking to amount of matches that can be made between commmand line inputs and words on a specific webpage
    Tree *freq = malloc(n_terms*sizeof(Tree));    
    assert(freq!=NULL);    

    for(int i = 0; i<argc; i++){
        freq[i]=NULL;
    }

    while(pageCounter < nurls){ //for each webpage
        List wordsOnPage = newList();   //to store all words that appear on webpage
        int match = 0;
        double tfidf = 0;
        parseWords(urls[pageCounter], wordsOnPage);     //insert all words found on webpage into wordsOnPage(list),
        for(int wordCounter = 1; wordCounter < argc; wordCounter++){ //for each word that we have to detect on the webpage
            match += find(wordsOnPage, argv[wordCounter]);    //add up total of how many of the desired words appear in the webpage
            tfidf += tf_idf(argv[wordCounter], urls[pageCounter], urls);
        }
        printf("URL: %s, match: %d, tfidf: %lf\n", urls[pageCounter], match, tfidf);
        Tree new = newTreeNode(urls[pageCounter], tfidf, match);
        printf("Created new Node\n");
        insertNode(freq[match-1], new);
        printf("Inserted Properly\n");
        //clearList(wordsOnPage);         
        pageCounter ++;
    }

    printf("Finished this part\n");

    while(output < 30 && !empty(freq[j])){  //supposed to output 30 results        
        printFromLargest(freq[j]);        
        j--;
        output++;    
    }
    return 0;
}
