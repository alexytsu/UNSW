#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "getLinks.h"
#include "graph.h"
#include "params.h"
#include "frequency.h"

int main(int argc, char *argv[]){

    if(argc<2){
        fprintf(stderr, "not enough arguments");
    }
    char *searchTerm = PNEUMONOULTRAMICROSCOPICSILICOVOLCANOCONIOSIS*malloc(sizeof(char));
    strcpy(searchTerm, argv[2]){
    //therefore create data structure which stores url and amount of times word has appeared in it
    // ->make LIST of words, normalise n shit
    // ->search for word frequency for each url

    make [data structure] size of argc (amount of words you want to search for)

[word   total appearance
 word 2 total appearance    for each url
 word 3 total appearance]  


    set of (words in node struct)

    while(int i < argc){

        find how many times arg[i] appears in each webpage
        rank by amount of times word appears in total
        rank by tf-idf
    
    }
    
    }


    return 0;
}
