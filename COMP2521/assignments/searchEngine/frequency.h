#ifndef FREQUENCY
#define FREQUENCY
#include "params.h"
#include "graph.h"
#include "linkedList.h"

double w_out(char *v, char*u, Graph linkMatrix, char urls[MAX_URLS][20], Webpage *pages);
double w_in(char* v, char* u, Graph linkMatrix, char urls[MAX_URLS][20], Webpage *pages);
OutputListNode *newOutputNode(Webpage *page);
void insertOrdered(OutputList *L, Webpage *page);
double tf(List l, char *term);
double idf(char *term);
double tf_idf(char *term, char *url, char urls[MAX_URLS][20]);
int urlCount(char sentence[MAX_LINE_LENGTH]);

#endif
