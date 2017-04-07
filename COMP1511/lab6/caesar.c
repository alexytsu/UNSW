#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 1000

int main(int c, char *argv[]){

    int offset = atoi(argv[1]), i = 0; 
    char input[MAX_LINE];

    while(fgets(input, MAX_LINE, stdin) != NULL){
        for(i = 0; i < MAX_LINE-1; i++){
            input[i] = 'a';            

        }
        printf("%s", input);
    }

    return 0;
}


