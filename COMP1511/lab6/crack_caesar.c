#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH 1000
#define ALPHABET 26

void read_frequencies(char input[], int frequencies[], int filemode, char encrypted[], char total_encrypted[]);

int main(int argc, char *argv[]){
    int sample_frequencies[ALPHABET] = {0};
    char total_encrypted[MAX_LENGTH];
    char encrypted[MAX_LENGTH];
    read_frequencies(argv[1], sample_frequencies, 1, encrypted, total_encrypted); 

    int most_frequent_sample = 0;
    int freq_of_most_frequent_sample = 0;

    for(int i = 0; i < ALPHABET; i ++){
        if(sample_frequencies[i] > freq_of_most_frequent_sample){
           freq_of_most_frequent_sample = sample_frequencies[i];
           most_frequent_sample = i;
        }
    }
    
    int encrypted_frequencies[ALPHABET] = {0};
    read_frequencies(argv[1], encrypted_frequencies, 0, encrypted, total_encrypted);

    int most_frequent_encrypted = 0;
    int freq_of_most_frequent_encrypted = 0;
    for(int i = 0; i < ALPHABET; i ++){
        if(encrypted_frequencies[i] > freq_of_most_frequent_encrypted){
           freq_of_most_frequent_encrypted = encrypted_frequencies[i];
           most_frequent_encrypted = i;
        }
    }

    int shift_length =  most_frequent_sample - most_frequent_encrypted;
    
    int total_length = strlen(encrypted);

    for(int i = 0; i < total_length; i++){
            if(encrypted[i] >= 'a' && encrypted[i] <= 'z'){
                if(encrypted[i] + shift_length > 'z'){
                    encrypted[i] += (shift_length-26);
                }else if(encrypted[i] + shift_length < 'a'){
                    encrypted[i] += (shift_length+26); 
                }else{
                    encrypted[i] += shift_length;
                } 
                printf("%c", encrypted[i]);
            }else if(encrypted[i] >= 'A' && encrypted[i] <= 'Z'){
                if(encrypted[i] + shift_length > 'Z'){
                    encrypted[i] += (shift_length-26);
                }else if(encrypted[i] + shift_length < 'A'){
                    encrypted[i] += (shift_length+26); 
                }else{
                    encrypted[i] += shift_length;
                } 
                printf("%c", encrypted[i]);
            }else{
                printf("%c", encrypted[i]);
            }
    }
    return 0;
}

void read_frequencies(char input[], int frequency[], int filemode, char encrypted[], char total_encrypted[]){

    int alphabet[ALPHABET] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    int upper_alphabet[ALPHABET] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    if(filemode){
        FILE *fp;
        fp = fopen(input, "r");
        int c;
        while(c != EOF){
            c = fgetc(fp);
            for(int i = 0; i < ALPHABET; i++){
                if(c == alphabet[i]){
                    frequency[i]++;
                    break;
                }else if(c == upper_alphabet[i]){
                    frequency[i]++;
                    break;
                }
            }
        }
    }else{
        
        int c;
        int pos = 0;
        while(c != EOF){
            c = fgetc(stdin); 
            if(c != EOF){
                for(int i = 0; i < ALPHABET; i++){
                    if(c == alphabet[i]){
                        frequency[i]++;
                    }else if(c == upper_alphabet[i]){
                        frequency[i]++;
                    }
                }
                encrypted[pos] = c;
                pos ++;
            }
        }

        /*while(fgets(encrypted, MAX_LENGTH, stdin)){
            length = strlen(encrypted);
            for(int i = 0; i < length; i++){
                for(int j = 0; j < ALPHABET; j++){
                    if(encrypted[i] == alphabet[j]){
                        frequency[j]++;
                        break;
                    }else if(encrypted[i] == upper_alphabet[j]){
                        frequency[j]++;
                        break;
                    }
                }
            }
        }*/
    }
}
