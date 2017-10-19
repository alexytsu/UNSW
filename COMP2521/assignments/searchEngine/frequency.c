#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "getLinks.h"
#include "graph.h"
#include "params.h"
#include "frequency.h"

//no. times word appears divided by total words.
double tf(char *term, char *url){
    

    return /wordCount();

}

//!! still have to implement max words from invertedIndex.

//total no. of docs divided by no. docs containing a specific term
double idf(char *term, int docCount){
    FILE *invIndex = fopen("invertedIndex.txt", "r");
    char urls[MAX_URLS][20];
    //total amount of webpages = total amount of urls
    double totalDoc = parseCollection("Sample1/collection.txt", urls);
    char lines[MAX_WORDS][MAX_LINE_LENGTH];  //stores lines from invertedIndex.txt
    int wordCount = 0;

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

    for (int findWord = 0; findWord<wordCount; findWord++){
        if(strcmp(first[findWord], term)==0) break;
    }
    int docsWithTerm = urlCount(lines[findWord]);

    return totalDoc/docsWithTerm;
}

//amount of words in a single document
double wordCount(){
        char urls[MAX_URLS][20];
}

int urlCount(char sentence[MAX_LINE_LENGTH]){

    int i = 0;
    int wordCount = 0;
    
    while(sentence[i]!='\n'){
        printf("%c", buff[1][j]);
        if(isspace(buff[1][j])) {
		wordCount++;
	}
        j++;
    }

//spaces lie between words
return wordCount+1;
}

//
int getWords(char *url, char wordArray[1000][40], Set *w)  //no. words containing max 40chars each
{
    char filename[30];

    strcpy(filename, "Sample1/");
    strcat(filename, url);
    strcat(filename, ".txt");

    FILE *fin = fopen(filename, "r");
    char buffer[1000];
    char word[40];
    int n_words=0;
    while(fgets(buffer, 1000, fin)){
        if(strcmp("#start Section-2\n", buffer) == 0) break;
    }
    //reading from section 2 onwards
    assert(strcmp(buffer, "#start Section-2\n")==0);    
    while(fscanf(fin, "%s", word) != -1){   
        if(strcmp(word, "#end") == 0) break;    //end scan when end is reached
                    
        n_words++;      //+1 word for each thing fscanf reads
        normalise(word);       //clean up the word
        insertInto(*w, word);   //insert word into array of sets
                
        strcpy(wordArray[n_words], word);   //copy read word into an array of words
    } 
    return 
}

double tfidf(char *term, int wCount, int docCount){
    return tf(term, wCount)*idf(term, docCount);
}
