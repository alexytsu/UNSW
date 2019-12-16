#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <ctype.h>

#include "params.h"
#include "linkedList.h"
#include "getLinks.h"
#include "set.h"
#include "neatening.h"
#include "frequency.h"
#include "graph.h"

OutputListNode *newNodeOutput(Webpage *page){
    OutputListNode *new = malloc(sizeof(OutputListNode *));
    new->page = page;
    new->next = NULL;
    return new;
}

void insertOrdered(OutputList *L, Webpage *page)
{
    OutputListNode *n = newNodeOutput(page);
    printf("%p\n", L);
    OutputListNode *curr = L->first;
    OutputListNode *prev = NULL;

    if(curr == NULL){
        printf("HI\n");
        L->first = L->last = n;
        return;
    }

    while(curr!=NULL && page->pageRank < curr->page->pageRank){
        prev = curr;
        curr = curr->next;
    }

    if(prev == NULL){
        L->first = n;
        n->next = curr;
    }else{
        prev->next = n;
        n->next = curr;
        if(n->next == NULL){
            L->last = n;
        }
    }
}

double w_in(char* v, char* u, Graph linkMatrix, char urls[MAX_URLS][20], Webpage *pages)
{

    double win = 0;
    //url11 -> url31

    int source = getIndex(v, urls);
    int dest = getIndex(u, urls);

    int destIncoming = 0;
    for(int i = 0; i < linkMatrix.nvertices; i ++){
        destIncoming += linkMatrix.edges[dest][i];
    }

    double sumOfInlinksOfPagesThatSourcePointsTo = 0; 
    for(int i = 0; i <  pages[source].n_outlinks; i ++){
        int pageThatSourcePointsTo = getIndex(pages[source].outlinks[i], urls); 
        for(int j = 0; j < linkMatrix.nvertices; j++){
            sumOfInlinksOfPagesThatSourcePointsTo += linkMatrix.edges[pageThatSourcePointsTo][j];
        }
    }

    win = (double) destIncoming/ (double) sumOfInlinksOfPagesThatSourcePointsTo;
    return win;
}

double w_out(char *v, char *u, Graph linkMatrix, char urls[MAX_URLS][20], Webpage *pages)
{ 
    double wout = 0.0;

    int source = getIndex(v, urls);
    int dest = getIndex(u, urls);

    double destOutgoing = (pages[dest].n_outlinks == 0) ? 0.5:pages[dest].n_outlinks;

    double sumOfOutlinksOfPagesThatSourcePointsTo = 0; 
    for(int i = 0; i <  pages[source].n_outlinks; i ++){
        int pageThatSourcePointsTo = getIndex(pages[source].outlinks[i], urls); 
        sumOfOutlinksOfPagesThatSourcePointsTo += (pages[pageThatSourcePointsTo].n_outlinks == 0) ? 0.5:pages[pageThatSourcePointsTo].n_outlinks;
    }

    wout = (double)destOutgoing/(double)sumOfOutlinksOfPagesThatSourcePointsTo;
    return wout;
}

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
    double totalDoc = parseCollection("collection.txt", urls);
    char line[MAX_LINE_LENGTH];

    int docsWithTerm = 0;
    //each line in invertedIndex is dedicated to a specific word, so no. words = no. lines
    while(fgets(line, MAX_LINE_LENGTH, invIndex)!=NULL){
        char *word = malloc(sizeof(char) * PNEUMONOULTRAMICROSCOPICSILICOVOLCANOCONIOSIS);
        sscanf(line, "%s", word);
        if(strcmp(term, word) == 0){
            docsWithTerm = urlCount(line);
        }
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
