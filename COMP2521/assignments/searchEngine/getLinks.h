int parseCollection(char *filename, char urls[MAX_URLS][20]);
Webpage newPage(char *url, int nurls);
int getOutgoingLinks(char *url, char **links);
void printPageDetails(Webpage page);
