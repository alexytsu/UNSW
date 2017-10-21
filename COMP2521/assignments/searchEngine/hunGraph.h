#include <stdio.h>

typedef struct vertex{
    char *url;
    double ratio;   
    struct vertex *next;

}vertex;

typedef struct rankRep{
    int rank;
    struct vertex *first;
    struct vertex *last;
}rankRep;

typedef struct *vertex Vertex;
typedef struct *rankRep = RankList;

RankList newRankList(int rank);
Vertex newVertex();

void addUrl(List l, char *url);

void showRatioList(List l);
void ratioRemoveNext(List l, Node keep); //removes element after keep
void ratioFilterList(List l);        //filters out duplicates in list

void calculateRatio(List l, int rank);  //assigns a ratio to each url respective to its rank in a specific file/list
void combineLists(List dest, List src); //merge src into dest with duplicates
void computeAvgRatio(List l);   //searches for duplicates, and averages their ratios

int rankListIntegrity(List l);
#endif
