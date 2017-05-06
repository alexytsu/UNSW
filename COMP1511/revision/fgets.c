#include <stdio.h>

int main(int argc, char *argv[]){
    char input[1000];
    while(fgets(input, 1000, stdin) != NULL){
        
        for(int i = 0; i < 1000; i ++){
            if(input[i] == '\n' || input[i] == EOF){
                break;
            }
            printf("%c\n", input[i]);
        }
    }
    return 0;
}
