#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 1000
int main(int argc, char *argv[]){

    FILE *fp;

	int alphabet[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	int upper_alphabet[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    int frequency[26] = {0};
    int frequency2[26] = {0};	
    fp = fopen(argv[1], "r");
    int c = 0;

    //find the frequency of each letter in the input text
    while(c != EOF){
        c = fgetc(fp);
        for(int i = 0; i < 26; i++){
            if(c == alphabet[i]){
                frequency[i]++;
                break;
            }else if(c == upper_alphabet[i]){
                frequency[i]++;
                break;
            }
        }
    }

    //make a list that orders the most frequent letters in the input text
    int index_of_max = 0;
    char ordered_by_freq[26] = {0};
    for(int k = 0; k < 26; k++){
        for(int j = 0; j < 26; j++){
            if(frequency[j] >= frequency[index_of_max]){
                index_of_max = j;
            } 
        }
        ordered_by_freq[k] = alphabet[index_of_max];
        frequency[index_of_max] = -1;
    }

    char message[MAX_LINE] = {'0'};
    int counter = 0;
    int d = 0; 
    while(d != EOF){
        d = fgetc(stdin);
        message[counter] = d;
        for(int i = 0; i < 26; i++){
            if(d == alphabet[i]){
                frequency2[i]++;
                break;
            }else if(d == upper_alphabet[i]){
                frequency2[i]++;
                break;
            }
        }
        counter ++;
    }


    index_of_max = 0;
    char ordered_by_freq2[26] = {0};
    for(int k = 0; k < 26; k++){
        for(int j = 0; j < 26; j++){
            if(frequency2[j] >= frequency2[index_of_max]){
                 index_of_max = j;
            }
       }
        ordered_by_freq2[k] = alphabet[index_of_max];
        frequency2[index_of_max] = -1;
    }


    for(int k = 0; k < counter; k++){
        for(int j = 0; j < 26; j++){
            if(message[k]>='a' &&  message[k] <='z'){
                if(message[k] == ordered_by_freq2[j]){
                    printf("%c", ordered_by_freq[j]);
                    break;
                }
            }else if(message[k]>='A' && message[k]<='Z'){
                if(message[k]-'A'+'a' == ordered_by_freq2[j]){
                    printf("%c", ordered_by_freq[j]-'a'+'A');
                    break;
                }
            }else{
                printf("%c", message[k]);
                break;
            }
        }
    }
    printf("\n");
    return 0;
}


