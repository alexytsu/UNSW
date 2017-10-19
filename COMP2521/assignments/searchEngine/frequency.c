#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "neatening.h"
#include "params.h"
#include "frequency.h"
#include "linkedList.h"
#include "math.h"

//no. times word appears in url divided by total words.
double tf(List l, char *term){     
    double retVal = (double)dupWordCount(l, term)/(double)length(l);
    return retVal;
}

//total no. of docs divided by no. docs containing a specific term
double idf(char *term){
    FILE *invIndex = fopen("invertedIndex.txt", "r");
    char urls[MAX_URLS][20];
    //total amount of webpages = total amount of urls
    double totalDoc = parseCollection("Sample1/collection.txt", urls);
    char line[MAX_LINE_LENGTH];

    int docsWithTerm = 0;
    printf("Handled inital FILE/IO\n");
    //each line in invertedIndex is dedicated to a specific word, so no. words = no. lines
<<<<<<< HEAD
    while(fgets(lines[wordCount], MAX_LINE_LENGTH, invIndex)!=NULL){
        //printf("%s\n", buff[wordCount]); //just for debugging
        wordCount++;  
    }


 /*   char *first = malloc(PNEUMONOULTRAMICROSCOPICSILICOVOLCANOCONIOSIS*sizeof(char *));
    for(int i = 0; i<PNEUMONOULTRAMICROSCOPICSILICOVOLCANOCONIOSIS; i++){
        first[i] = malloc(20*sizeof(char)); 
    }*/

    //holds first character of each line, which should be the word
    for(int j = 0; j<wordCount; j++){        
        sscanf(lines[j], "%s", first[j]);
        printf("j=%d, first word is %s \n", j, first[j]);
    }

    for (findWord = 0; findWord<wordCount; findWord++){
        if(strcmp(first[findWord], term)==0) break;
    }
    return log1p((double)docsWithTerm/(double)totalDoc);
}

int urlCount(char sentence[MAX_LINE_LENGTH]){
    int i = 0;
    int wordCount = 0;
    
    while(sentence[i]!='\n'){
        if(isspace(sentence[i])){
            wordCount++;
        }
        i++;
    }
    return wordCount;
}

double tf_idf(char *term, char *url, char urls[MAX_URLS][20]){
    List words = newList(); 
    parseWords(url, words);
    return tf(words, term)*idf(term);
}
