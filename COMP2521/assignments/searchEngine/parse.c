#include <stdio.h>

int main()
{
    getCollection("Sample1/collection.txt");
}

void getCollection(char *filename)
{
    FILE fin = fopen("filename", "r");
    int links[100] = {-1};
    int link_count = 0;
    while(fscanf(fin, "%url%d", &links[link_count]) != EOF){
        printf("%d\n", links[link_count]);
        link_count++;
    }
}
