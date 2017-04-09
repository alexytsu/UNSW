#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LENGTH 1000


int main(int argc, char *argv[]){

    char codedmessage[MAX_LENGTH];
        
    //read the input into message
    while(fgets(codedmessage, MAX_LENGTH, stdin)!=NULL){

        //get the length of the coded message
        int length = strlen(codedmessage); 
        char decrypted[length];

        //loop through the message; while inside this loop, codedmessage[i]
        //is the letter at position i in the untranslated message
        for(int i = 0; i < length; i++){
            
            if(codedmessage[i] >= 'a' && codedmessage[i] <= 'z'){

                //this for loop runs 26 times, which allows us to see into the
                //cipher by accessing argv[1][j]
                for(int j = 0; j < 26; j++){
                    //check if the letter from the message currently being 
                    //analysed is at position j in the cipher
                    if(argv[1][j] == codedmessage[i]){
                        //when this if statement succeeds, then the letter is 
                        //at position j in the cipher
                        //note that ('a' + j) is the ASCII value of the original
                        //unciphered character
                        
                        //so the decrypted message is j letters away from 'a'
                        decrypted[i] = 'a' + j;
                        break;
                    }
                }
                putchar(decrypted[i]);
            }else if(codedmessage[i] >= 'A' && codedmessage[i] <= 'Z'){
                for(int j = 0; j < 26; j++){
                    if(argv[1][j]+'A'-'a' == codedmessage[i]){
                        decrypted[i] = 'A' + j;
                        break;
                    }
                }
                putchar(decrypted[i]);
            }else{
                putchar(codedmessage[i]);
            }
        }
    }
    return 0;
}
