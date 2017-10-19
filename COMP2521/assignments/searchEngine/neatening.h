#include <stdio.h>
#include "params.h"
#include "linkedList.h"
#include "set.h"

void normalise(char *word);
void parseWords(char *url, List l);
void getWords(char *url, char wordArray[1000][40], Set *w);
