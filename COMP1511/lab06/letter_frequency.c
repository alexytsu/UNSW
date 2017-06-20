#include <stdio.h>
#include <string.h>
#define MAX_LINE 1000

int main(void) {
    int alphabet[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    int upper_alphabet[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    int counter[26] = {0}, prev_counter[26] = {0}, i=0, j=0, k=0;
    double character_count=0, prev_character_count;
    char input[MAX_LINE];
    //counts the number of each character from the input
    while(fgets(input, MAX_LINE, stdin) != NULL) {
        for(i; i < strlen(input); i++) {
            for(j; j < 26; j++) { 
                if(input[i] == alphabet[j] || input[i] == upper_alphabet[j]) {
                    counter[j]++;
                    //counts the total characters
                    character_count++;
                } 
            }
            j=0;
        }
        i=0;
    }
    //prints out the frequency of the character and percentage
    for(k; k < 26; k++) {
        printf("'");
        putchar(alphabet[k]);
        printf("' %lf %d\n", counter[k]/character_count, counter[k]);
    }
    return 0;	
}
