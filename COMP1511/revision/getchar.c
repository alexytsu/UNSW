#include <stdio.h>

int main(void){

    int input[200];
    int c = getchar();
    int count = 0;
    while(c!=EOF){
        input[count] = c;
        c = getchar();
        count ++;
    }
    for(int i = 0; i < count; i++){
        printf("%d", input[i]);
    }
    printf("\n");
    for(int i = 0; i < count; i++){
        printf("%c", input[i]);
    }

    return 0;
}
