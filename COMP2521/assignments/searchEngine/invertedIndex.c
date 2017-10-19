#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <malloc.h>
#include <ctype.h>
#include "getLinks.h"
#include "graph.h"
#include "params.h"
#include "set.h"
#include "linkedList.h"
#include "neatening.h"


int main(int argc, char *argv[]){

    //Get urls from collection.txt
    char urls[MAX_URLS][20];
    int nurls;
    printf("Number of pages: %d\n", nurls = parseCollection("Sample1/collection.txt", urls));
    
    printf("====================== Initializing Pages ======================\n");
    //Create an array of all pages
    Webpage *pages = malloc(sizeof(Webpage) * nurls);
    
    for(int i = 0; i < nurls; i++){
        printf("Creating a webpage for %s\n", urls[i]);
        pages[i] = newPage(urls[i], nurls);
    }   
    
    char wordsInUrl[1000][PNEUMONOULTRAMICROSCOPICSILICOVOLCANOCONIOSIS];

    Set *wordSetArray = malloc(nurls*sizeof(Set));  //creates an array of sets of words in each webpage.
    for(int i = 0; i <nurls; i++){
        wordSetArray[i] = newSet();
    }
    //for each webpage get the words that are on its page.
    for(int urlCount=0; urlCount<nurls; urlCount++){
        getWords(urls[urlCount], wordsInUrl, &wordSetArray[urlCount]);	
	
    }


    //make a list of all words that appear across all webpages
    List wordIndex = newList();
    //for each webpage

    char *nextWord = NULL;
    for(int indexCount=0; indexCount<nurls; indexCount++){   

        //nextword stores in the next item in the set of words that belong to one webpage 
        while(!isEmpty(wordSetArray[indexCount])){

            nextWord = nextElem(wordSetArray[indexCount]);
            //that word is inserted into the overarching index
            insertWord(wordIndex, nextWord);
//printf("%s\n", nextWord);
            //the webpage the word is taken from is listed as containing that word
            insertUrl(wordIndex, nextWord, urls[indexCount]);
        }

    }
printf("word index successful:\n");
showList(wordIndex);
filterList(wordIndex);
printf("\n");
showList(wordIndex);
    FILE *fout = fopen("invertedIndex.txt", "w");
    printIndex(wordIndex, fout);
    fclose(fout);
}
