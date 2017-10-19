#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "getLinks.h"
#include "graph.h"
#include "params.h"

double tf(char *term, int wCount);
double idf(char *term, int docCount);
double tfidf(char *term, int wCount, int docCount);
