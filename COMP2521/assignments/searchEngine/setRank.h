#ifndef SETRANK_H
#define SETRANK_H

typedef struct SetRep *Set;

// Function signatures

Set newSetRank();
void disposeSetRank(Set);
void insertIntoRank(Set,char *);
void dropFromRank(Set,char *);
void copySet(Set, Set);
int  isElemRank(Set,char *);
int  nElemsRank(Set);
void showSetRank(Set);
char *nextElemRank(Set);
int isEmptyRank(Set);
void insertPRank(Set s, int *pVector);
int findPRank(Set s, char *url);

#endif
