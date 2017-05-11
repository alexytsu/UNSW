#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    FILE *fin;

    if(argc == 2){//print the first 10 lines
        fin = fopen(argv[1], "r");
        char curLine[1024];
        for(int i = 0; i < 10; i ++){
            if(fgets(curLine, 1024, fin)!=NULL){
                printf("%s", curLine);
            }else{
                return 0;
            }
        }
    }

    if(argc == 4 && (argv[1][0] == '-' && argv[1][1] == 'n')){
        int lines = atoi(argv[2]);
        
        fin = fopen(argv[3], "r");
        char curLine[1024];
        for(int i = 0; i < lines; i ++){
            if(fgets(curLine, 1024, fin)!=NULL){
                printf("%s", curLine);
            }else{
                return 0;
            }
        }
    }

    return 0;
}
