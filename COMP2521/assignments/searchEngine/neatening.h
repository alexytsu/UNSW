#ifndef NEATENING
#define NEATENING
#include "linkedList.h"

void normalise(char *word);
void parseWords(char *url, List l);
void getWords(char *url, char wordArray[1000][40], Set *w);
#endif
