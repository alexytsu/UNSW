#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include "set.h"
#include "neatening.h"

void normalise(char *word){
    for(int ch = 0; word[ch]!='\0'; ch++){
            word[ch] = tolower(word[ch]);
            if (!isalpha(word[ch])){
                word[ch]='\0';
            }
    }
}

void getWords(char *url, char wordArray[1000][40], Set *w)  //no. words containing max 40chars each
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
}

void parseWords(char *url, List l)  //parses through words on a specific webpage, chucks it all into list l
{
    char filename[30];

    strcpy(filename, "Sample1/");
    strcat(filename, url);
    strcat(filename, ".txt");

    FILE *fin = fopen(filename, "r");
    char buffer[1000];
    char word[PNEUMONOULTRAMICROSCOPICSILICOVOLCANOCONIOSIS];
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
        insertWordsInPage(l, word);   //insert word into linked list for each webpage
    } 
}

