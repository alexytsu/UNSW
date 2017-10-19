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
    int n_possible_matches = argc;
    int pageCounter = 0;
   
     
    //array of trees linking to amount of matches that can be made between commmand line inputs and words on a specific webpage
    Tree *freq = malloc(n_possible_matches*sizeof(Tree));    
    for(int i = 0; i < n_possible_matches; i++){
        freq[i] = malloc(sizeof(Tree));
    }
    assert(freq!=NULL);    

    for(int i = 0; i<argc; i++){
        freq[i]=NULL;
    }

    while(pageCounter < nurls){ //for each webpage
        printf("================ LOOKING AT %s ============\n", urls[pageCounter]);
        List wordsOnPage = newList();   //to store all words that appear on webpage
        int match = 0;
        double tfidf = 0;
        parseWords(urls[pageCounter], wordsOnPage);     //insert all words found on webpage into wordsOnPage(list),
        for(int wordCounter = 1; wordCounter < argc; wordCounter++){ //for each word that we have to detect on the webpage
            match += find(wordsOnPage, argv[wordCounter]);    //add up total of how many of the desired words appear in the webpage
            tfidf += tf_idf(argv[wordCounter], urls[pageCounter], urls);
            printf("\tWord: %s: %d, tfidf: %.6lf\n", argv[wordCounter],
                    find(wordsOnPage, argv[wordCounter]),
                    tf_idf(argv[wordCounter], urls[pageCounter], urls)); //add up total of how many of the desired words appear in thelllllwebpage 
        }
        assert(match-1 <= n_terms);
        printf("\tURL: %s, match: %d, tfidf: %lf\n", urls[pageCounter], match, tfidf);
        printf("\tCreated new Node\n");
        freq[match] = insertNodeWithValues(freq[match], tfidf, match, urls[pageCounter]);
        //Tree new = newTreeNode(urls[pageCounter], tfidf, match);
        //freq[match-1] = insertNode(freq[match-1], new);
        printf("\tInserted Properly\n");
        printf("\tChecking tree\n\t\t");
        printTree(freq[match]);
        //clearList(wordsOnPage);         
        pageCounter ++;
    }

    printf("Finished this part\n");
    for(int i = n_possible_matches-1; i > 0; i --){
        printf("Array holding tree with %d matches has address %p\n", i, freq[i]);
        printFromLargest(freq[i]); 
    }
    return 0;
}
