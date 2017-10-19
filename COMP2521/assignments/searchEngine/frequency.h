#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "getLinks.h"
#include "params.h"
#include "linkedList.h"

double tf(List l, char *term);
double idf(char *term);
double tf_idf(char *term, char *url, char urls[MAX_URLS][20]);
int urlCount(char sentence[MAX_LINE_LENGTH]);
