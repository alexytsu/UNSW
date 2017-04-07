#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH 1000

int main(int c, char *argv[]){

    //get the caesar shift width
    int shift = atoi(argv[1]) % 26;
    
    while(1){
        //get the message to be shifted
        char message[MAX_LENGTH];
        fgets(message, MAX_LENGTH, stdin);

        //perform the caesar shift on the message
        int length = strlen(message); 
        for(int i = 0; i < length; i++){
            char cur = message[i]; 

            if(cur >= 'a' && cur <= 'z'){
                cur = ();
                putchar(cur);

            }else if(cur >= 'A' && cur <= 'Z'){

            }
        }

        //print the ciphered message
        printf("%s", message);

    }
    return 0;
}
