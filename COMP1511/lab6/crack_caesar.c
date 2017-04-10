#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 1000
int main(int argc, char *argv[]){

    FILE *fp;

	int alphabet[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	int upper_alphabet[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    int frequency[26] = {0};
	
    fp = fopen(argv[1], "r");
    int c;

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

    for(int k = 0; k < 26; k++){
        printf("%c: %d\n", alphabet[k], frequency[k]);
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

    for(int k = 0; k < 26; k++){
        printf("%c\n", ordered_by_freq[k]);
    }

    

    return 0;
}
