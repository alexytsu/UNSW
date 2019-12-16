#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>

#include "params.h"

typedef struct rankedResultEntry{
    char *url;
    double pageRank;
    struct rankedResultEntry *next;
    int matches;
}RankedResultEntry;

typedef RankedResultEntry * Entry;

Entry createEntry(char *url, double pageRank)
{
    Entry newEntry = malloc(sizeof(Entry));
    strcpy(newEntry->url, url);


    return newEntry;
}

int getPageRanksIndexFromUrl(char *url, RankedResultEntry PageRanks[MAX_URLS])
{
    for(int i = 0; i < MAX_URLS; i++){
        if(strcmp(url, PageRanks[i].url) == 0){
            return i;
        }
    }
    return -1;
}



void printList(Entry list)
{
    for(Entry curr = list; curr != NULL; curr = curr->next){
        //printf("%s[%.3lf]-> ", curr->url, curr->pageRank);
    }
    //printf("x\n");
}

Entry deleteEntry(Entry list, Entry toDelete){
    if(list->next == NULL){
        assert(list == toDelete);
        return NULL;
    }
    if(list == toDelete){
        return list->next;
    }
    Entry curr = list;
    Entry prev = NULL;
    while(curr != toDelete){
        prev = curr;
        curr = curr->next;
    }
    prev ->next = curr->next;
    return list;
}

Entry insertEntry(Entry head, Entry n)
{
    Entry curr = head;
    Entry prev = NULL;
    //printf("\t\tInserting an entry for %s\n", n->url);
    //printf("\t\t\t the list about to be inserted into looks like this\n\t\t\t");
    printList(head);

    //if the list is empty
    if(curr == NULL){
        n->next = NULL;
        return n;
    }

    while(curr!=NULL && n->pageRank < curr->pageRank){
        prev = curr;
        curr = curr->next;
    }

    if(prev == NULL){
        n->next = head;
        return n;
    }else{
        prev->next = n;
        n->next = curr;
        return head;
    }
}
int main(int argc, char *argv[])
{

    int nSearchTerms = argc-1;
    //printf("SEARCH TERMS\n");
    for(int i = 1; i < argc; i ++){
        //printf("%s ", argv[i]);
    }

    //printf("\n===============================\n");

    //an array of entries becomes our results
    Entry *results = malloc(sizeof(Entry) * nSearchTerms); 
    for(int i = 0; i < nSearchTerms; i ++){
        results[i] = NULL;
    }

    FILE *f_index = fopen("invertedIndex.txt", "r");
    //printf("Successfully opened index\n");
    FILE *f_pageRank = fopen("pagerankList.txt", "r");
    //printf("Successfully pagerank list\n");
    RankedResultEntry *PageRanks = malloc(sizeof(RankedResultEntry) * MAX_URLS);
    char line[MAX_LINE_LENGTH];

    int entries = 0;
    while(fgets(line, MAX_LINE_LENGTH, f_pageRank) != NULL){
        char *url = malloc(sizeof(char) * 1000);
        int outlinks;
        double pagerank;
        sscanf(line, "%s %d, %lf", url, &outlinks, &pagerank);
        url[strlen(url)-1] = '\0';
        //printf("%s %d %.7lf\n", url, outlinks, pagerank);
        PageRanks[entries].url = malloc(sizeof(char) * 20);
        strcpy(PageRanks[entries].url, url);
        PageRanks[entries].pageRank = pagerank;
        PageRanks[entries].matches = 0;
        PageRanks[entries].next = NULL;
        entries ++;
    }

    while(fgets(line, MAX_LINE_LENGTH, f_index) != NULL){
        char *term = malloc(sizeof(char) * PNEUMONOULTRAMICROSCOPICSILICOVOLCANOCONIOSIS);
        sscanf(line, "%s", term);
        //printf("Looking at index term %s\n", term);
        for(int i = 1; i <= nSearchTerms; i++){
            if(strcmp(term, argv[i]) == 0){
                //printf("\tMatched with a term in the index\n");
                
                //here term is an entry in the index that matches a search term
                //term is the first word in buffer "line" which holds all the urls containing the term
                
                char *page = strtok(line, " "); 
                while((page = strtok(NULL, " ")) != NULL){ 
                    if(page[strlen(page)-1] == '\n'){
                        page[strlen(page)-1] = '\0';
                    }
                    //printf("\t\tPage: %s\n", page);
                    int index = getPageRanksIndexFromUrl(page, PageRanks); 
                    //printf("\t\t Got that boi index here %d\n", index);
                    //printf("\t\t Is it really tho? Let's check PageRanks[%d]: %s\n", index, PageRanks[index].url);
                    assert(index != -1);
                    Entry newPage = &PageRanks[index]; 

                    //insertPageIntoResults(results, newPage);=================

                    int matches = newPage->matches;
                    if(matches > 0){
                        //printf("PRINTING LIST TO DELETE STUFF FROM\n");
                        printList(results[matches-1]);
                        results[matches-1] = deleteEntry(results[matches-1], newPage);
                        //printf("PRINTING LIST AFTER DELETION\n");
                        printList(results[matches-1]);
                    }
                    results[matches] = insertEntry(results[matches], newPage);
                    //printf("\t\t\tPRINTING AFTER INSERT\n\t\t\t");
                    printList(results[matches]);
                    newPage->matches++;
                    // =========================================================
                }
            }
        }
    }

    int entriesPrinted = 0;

    for(int nmatched = nSearchTerms-1; nmatched >= 0; nmatched --){
        for(Entry curr = results[nmatched]; curr != NULL; curr = curr->next){
            entriesPrinted ++;
            printf("%s\n", curr->url);
            if(entriesPrinted == 30) break;
        }
        if(entriesPrinted == 30) break;
    }
}
