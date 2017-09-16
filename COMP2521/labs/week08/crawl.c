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
#define DEBUGGING 0
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
     
	// You need to modify the code below to implement:
	//
	// add firstURL to the ToDo list
	// DONE initialise Graph to hold up to maxURLs
	// DONE initialise set of Seen URLs
	// while (ToDo list not empty and Graph not filled) {
	//    grab Next URL from ToDo list
	//    if (not allowed) continue
	//    foreach line in the opened URL {
	//       foreach URL on that line {
	//          if (Graph not filled or both URLs in Graph)
	//             add an edge from Next to this URL
	//          if (this URL not Seen already) {
	//             add it to the Seen set
	//             add it to the ToDo list
	//          }
	//       }
    //    }
	//    close the opened URL
	//    sleep(1)
	// }

    pushOnto(toVisit, firstURL);

    /*
	if (!(handle = url_fopen(firstURL, "r"))) {
		fprintf(stderr,"Couldn't open %s\n", next);
		exit(1);
	}
    */
    int nVisited = 0;

    while(!emptyStack(toVisit)){
        //get the next url to visit
        strcpy(next, popFrom(toVisit));

        //check if already seen
        if(isElem(visited, next)){ 
            if(DEBUGGING){
                printf("Skipping %s because already visited\n", next);
            }
            continue;
        }

        if(nVisited >= maxURLs) break;

        handle = url_fopen(next, "r");
        nVisited ++;
        if(DEBUGGING){
            printf("Visiting %s\n", next);
        }

        while(!url_feof(handle)) {
            url_fgets(buffer,sizeof(buffer),handle);
            if(DEBUGGING && VERBOSE){
                fputs(buffer,stdout);
            }
            int pos = 0;
            char result[BUFSIZE];
            memset(result,0,BUFSIZE);
            while ((pos = GetNextURL(buffer, firstURL, result, pos)) > 0) {
                if(DEBUGGING){
                    printf("Found: '%s'\n",result);
                }
                addEdge(webGraph, next, result);
                if(DEBUGGING && VERBOSE){
                    showGraph(webGraph,1);
                }
                pushOnto(toVisit,result);
                memset(result,0,BUFSIZE);
            }
        }
        insertInto(visited, next);
        url_fclose(handle);
        sleep(1);
        
    }

    showGraph(webGraph, 0);
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
