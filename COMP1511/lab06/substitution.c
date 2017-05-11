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
                putchar(argv[1][message[i]-'a']);
            }else if(message[i] >= 'A' && message[i] <= 'Z'){
                putchar(argv[1][message[i]-'A']-'a'+'A');
            }else{
                putchar(message[i]);
            }
        }
    }
    return 0;
}
