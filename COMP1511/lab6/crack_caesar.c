#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 1000
int main(int argc, char *argv[]){

    FILE *fp;
	int alphabet[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	int upper_alphabet[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
	
	int counter[26] = {0}, prev_counter[26] = {0}, i=0, j=0, k=0;
	double character_count=0, prev_character_count;
	
    fp = fopen(argv[1], "r");

    int c;
    while(c != EOF){
        c = fgetc(fp);
        printf("read a ’%d’\n", c);
    }
    return 0;
}
