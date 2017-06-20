#include <stdio.h>
#include <string.h>

int main(void){

    char cur = getchar();
    int freq[26] = {0};
    int total_letters = 0;
    int index;
    while(cur!=EOF){
        if('a' <= cur && cur <= 'z'){
            index = cur-'a';
            total_letters++; 
            freq[index] ++;
        }else if('A' <= cur && cur <= 'Z'){
            index = cur-'A';
            total_letters++;
            freq[index] ++;
        }
        cur = getchar();
    }

    for(int i = 0; i < 26; i ++){
        printf("'%c' %lf %d\n", 'a'+i, (double)freq[i]/total_letters, freq[i]);
    }

}
