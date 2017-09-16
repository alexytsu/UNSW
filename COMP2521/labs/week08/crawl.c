// crawl.c ... build a graph of part of the web
// Written by John Shepherd, September 2015
// Uses the cURL library and functions by Vincent Sanders <vince@kyllikki.org>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <curl/curl.h>
#include "stack.h"
#include "set.h"
#include "graph.h"
#include "html.h"
#include "url_file.h"

#define BUFSIZE 1024
#define DEBUGGING 1
#define VERBOSE 0

void setFirstURL(char *, char *);
void normalise(char *, char *, char *, char *, int);

int main(int argc, char **argv)
{
	URL_FILE *handle;
	char buffer[BUFSIZE];
	char baseURL[BUFSIZE];
	char firstURL[BUFSIZE];

	char next[BUFSIZE];

	int  maxURLs;

    // Check command line arguments for validity
	if (argc > 2) {
		strcpy(baseURL,argv[1]);
		setFirstURL(baseURL,firstURL);
		maxURLs = atoi(argv[2]);
		if (maxURLs < 40) maxURLs = 40;
	}
	else {
		fprintf(stderr, "Usage: %s BaseURL MaxURLs\n",argv[0]);
		exit(1);
	}

    // Create the empty Graph
    Graph webGraph = newGraph(maxURLs);
    if(DEBUGGING){
        printf("Show the empty webGraph\n");
        showGraph(webGraph, 1);
    }

    // Create set of seen URLs
    Set visited = newSet();

    // Create a stack of URLs to visit
    Stack toVisit = newStack();
     

    // Add the firstURL to the ToDo list
    pushOnto(toVisit, firstURL);


    // Keep track of visited webpages to compare against maxURLs
    int nVisited = 0;

    while(!emptyStack(toVisit) && nVisited <= maxURLs){

        //get the next url to visit
        strcpy(next, popFrom(toVisit));

        // check if already seen
        if(isElem(visited, next)){ 
            if(DEBUGGING && VERBOSE){
                printf("Skipping %s because already visited\n", next);
            }
            continue;
        }

        // if new, open the webpage
        handle = url_fopen(next, "r");
        nVisited ++;
        if(DEBUGGING){
            printf("Visiting %s\n", next);
        }

        // loop through the webpage
        while(!url_feof(handle)) {
            url_fgets(buffer,sizeof(buffer),handle);
            if(DEBUGGING && VERBOSE){
                fputs(buffer,stdout);
            }
            int pos = 0;
            char result[BUFSIZE];
            memset(result,0,BUFSIZE);
            // jump to each URL
            while ((pos = GetNextURL(buffer, firstURL, result, pos)) > 0) {
                if(DEBUGGING && VERBOSE){
                    printf("Found: '%s'\n",result);
                }

                // add each new URL to the graph and toDo list
                addEdge(webGraph, next, result);
                if(DEBUGGING && VERBOSE){
                    showGraph(webGraph,1);
                }
                pushOnto(toVisit,result);
                memset(result,0,BUFSIZE);
            }
        }
        
        //every visited page gets added to a set of visited pages
        insertInto(visited, next);
        url_fclose(handle);
        sleep(1);
        
    }


    showGraph(webGraph, 0);
    disposeGraph(webGraph);
    disposeSet(visited);
    disposeStack(toVisit);
	return 0;
}

// setFirstURL(Base,First)
// - sets a "normalised" version of Base as First
// - modifies Base to a "normalised" version of itself
void setFirstURL(char *base, char *first)
{
	char *c;
	if ((c = strstr(base, "/index.html")) != NULL) {
		strcpy(first,base);
		*c = '\0';
	}
	else if (base[strlen(base)-1] == '/') {
		strcpy(first,base);
		strcat(first,"index.html");
		base[strlen(base)-1] = '\0';
	}
	else {
		strcpy(first,base);
		strcat(first,"/index.html");
	}
}
