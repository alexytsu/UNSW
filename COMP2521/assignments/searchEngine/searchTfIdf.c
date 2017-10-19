#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "graph.h"
#include "params.h"
#include "frequency.h"
#include "bstree.h"
#include "linkedList.h"
#include "neatening.h"

int main(int argc, char *argv[]){

    if(argc<2){
        fprintf(stderr, "not enough arguments");
    }
    
    char urls[MAX_URLS][20];
    
    double tfidf = 0;
    int nurls = parseCollection("Sample1/collection.txt", urls);
    int match = 0;
    int output = 0;
    int pageCounter = 0;
    int j = argc;
    
    //array of trees linking to amount of matches that can be made between commmand line inputs and words on a specific webpage
    Tree *freq = malloc((argc-1)*sizeof(Tree));    
    assert(freq!=NULL);    
    for(int i = 0; i<argc; i++){
        freq[i]=NULL;
    }
    
    
    List wordsOnPage = newList();   //to store all words that appear on webpage
    while(pageCounter < nurls){ //for each webpage
        parseWords(urls[pageCounter], wordsOnPage);     //insert all words found on webpage into wordsOnPage(list),
        for(int wordCounter = 1; wordCounter < argc; wordCounter++){ //for each word that we have to detect on the webpage
            match += find(wordsOnPage, argv[wordCounter]);    //add up total of how many of the desired words appear in the webpage
            tfidf = tf(wordsOnPage, url[pageCounter])*idf(argv[wordCounter], nurls);
        }
        insertPage(freq[match-1], url[pageCounter], tfidf);    //insert url into frequency tree
        clearList(wordsOnPage);         
    }

    while(output < 30 && !empty(freq[j])){  //supposed to output 30 results        
            printFromLargest(freq[j]);        
        j--;
        output++;    
    }
    
    


    return 0;
}
