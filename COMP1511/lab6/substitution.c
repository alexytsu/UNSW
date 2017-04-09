#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LENGTH 1000

int main(int argc, char *argv[]){
    char message[MAX_LENGTH];
    while(fgets(message, MAX_LENGTH, stdin)!=NULL){
        //get the message to be shifted
        int length = strlen(message); 
        for(int i = 0; i < length; i++){
            if(message[i] >= 'a' && message[i] <= 'z'){
                message[i] = argv[1][message[i]-'a']; 
                putchar(message[i]);
            }else if(message[i] >= 'A' && message[i] <= 'Z'){
                message[i] = argv[1][message[i]-'A']-'a'+'A'; 
                putchar(message[i]);
            }else{
                putchar(message[i]);
            }
        }
    }
    return 0;
}
