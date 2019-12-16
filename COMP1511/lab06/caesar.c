#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH 1000

int main(int c, char *argv[]){

    //get the caesar shift width
    int shift = atoi(argv[1]) % 26;

    char message[MAX_LENGTH];
    while(fgets(message, MAX_LENGTH, stdin)!=NULL){
        //get the message to be shifted

        //perform the caesar shift on the message
        int length = strlen(message); 
        for(int i = 0; i < length; i++){
            if(message[i] >= 'a' && message[i] <= 'z'){
                if(message[i] + shift > 'z'){
                    message[i] += (shift-26);
                }else if(message[i] + shift < 'a'){
                    message[i] += (shift+26); 
                }else{
                    message[i] += shift;
                } 
                putchar(message[i]);
            }else if(message[i] >= 'A' && message[i] <= 'Z'){
                if(message[i] + shift > 'Z'){
                    message[i] += (shift-26);
                }else if(message[i] + shift < 'A'){
                    message[i] += (shift+26); 
                }else{
                    message[i] += shift;
                } 
                putchar(message[i]);
            }else{
                putchar(message[i]);
            }
        }
    }
    return 0;
}
