#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LENGTH 1000


int main(int argc, char *argv[]){

    char message[MAX_LENGTH];
    while(fgets(message, MAX_LENGTH, stdin)!=NULL){
        int length = strlen(message); 
        for(int i = 0; i < length; i++){

            if(message[i] >= 'a' && message[i] <= 'z'){
                for(int j = 0; j < 26; j++){
                    if(argv[1][j] == message[i]){
                        message[i] = 'a' + j;
                        break;
                    }
                }
                putchar(message[i]);
            }else if(message[i] >= 'A' && message[i] <= 'Z'){
                for(int j = 0; j < 26; j++){
                    if(argv[1][j]+'A'-'a' == message[i]){
                        message[i] = 'A' + j;
                        break;
                    }
                }
                putchar(message[i]);
            }else{
                putchar(message[i]);
            }
        }
    }
    return 0;
}
