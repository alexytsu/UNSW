#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "getLinks.h"
#include "params.h"
#include "linkedList.h"

double tf(List l, char *term);
double idf(char *term, int docCount);
double tfidf(char *term, int wCount, int docCount);
int urlCount(char sentence[MAX_LINE_LENGTH]);
