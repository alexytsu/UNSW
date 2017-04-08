#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LENGTH 1000


int main(int argc, char *argv[]){
    char cipher[26];
    strcpy(cipher, argv[1]);
    while(1){
        //get the message to be shifted
        char message[MAX_LENGTH];
        fgets(message, MAX_LENGTH, stdin);

        int length = strlen(message); 
        for(int i = 0; i < length; i++){
            
            if(message[i] >= 'a' && message[i] <= 'z'){
                message[i] = cipher[message[i]-'a']; 
                putchar(message[i]);
            }else if(message[i] >= 'A' && message[i] <= 'Z'){
                message[i] = cipher[message[i]-'A']-'a'+'A'; 
                putchar(message[i]);
            }else{

                putchar(message[i]);
            }
        }
    }
    return 0;
}
