typedef struct pageID{
    char *name;
    int id;
}PageID;

typedef struct webpage{
    char *name;    
    int n_outlinks;
    char** outlinks;

    PageID* outIDs;
    
    
    double pageRank;
}Webpage;

#define MAX_URLS 1000

int parseCollection(char *filename, char urls[MAX_URLS][20]);
Webpage newPage(char *url, int nurls);
int getOutgoingLinks(char *url, char **links);
void printPageDetails(Webpage page);

