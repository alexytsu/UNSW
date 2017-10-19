#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "neatening.h"
#include "params.h"
#include "frequency.h"
#include "linkedList.h"

//no. times word appears in url divided by total words.
double tf(List l, char *term){     
    return dupWordCount(l, term)/length(l);
}


//total no. of docs divided by no. docs containing a specific term
double idf(char *term, int docCount){
    FILE *invIndex = fopen("invertedIndex.txt", "r");
    char urls[MAX_URLS][20];
    //total amount of webpages = total amount of urls
    double totalDoc = parseCollection("Sample1/collection.txt", urls);
    char lines[MAX_WORDS][MAX_LINE_LENGTH];  //stores lines from invertedIndex.txt
    int wordCount = 0;
    int findWord = 0;

    //each line in invertedIndex is dedicated to a specific word, so no. words = no. lines
    while(fgets(lines[wordCount], MAX_LINE_LENGTH, invIndex)!=NULL){
        //printf("%s\n", buff[wordCount]); //just for debugging
        wordCount++;  
    }

    //holds first character of each line, which should be the word
    char *first = malloc(PNEUMONOULTRAMICROSCOPICSILICOVOLCANOCONIOSIS*sizeof(char *));
    for(int i = 0; i<PNEUMONOULTRAMICROSCOPICSILICOVOLCANOCONIOSIS; i++){
        first[i] = malloc(20*sizeof(char)); 
    }

    for(int j = 0; j<wordCount; j++){        
        sscanf(lines[j], "%s", first[j]);
        printf("j=%d, first word is %s \n", j, first[j]);
    }

    for (findWord = 0; findWord<wordCount; findWord++){
        if(strcmp(first[findWord], term)==0) break;
    }
    int docsWithTerm = urlCount(lines[findWord]);

    return totalDoc/docsWithTerm;
}


int urlCount(char sentence[MAX_LINE_LENGTH]){

    int i = 0;
    int wordCount = 0;
    
    while(sentence[i]!='\n'){
        printf("%c", sentence[j]);
        if(isspace(sentence[j])) {
		wordCount++;
	}
        j++;
    }

//spaces lie between words
return wordCount+1;
}

//


double tfidf(char *term, int wCount, int docCount){
    return tf(term, wCount)*idf(term, docCount);
}
