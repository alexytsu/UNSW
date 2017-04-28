#include <stdio.h>
#define MAX 1000

int main(void){
    
    int num;
    int input[MAX];
    int counter = 0;
    while(scanf("%d", &num) != EOF){
        input[counter] = num;
        counter ++;
    }
    
    for(int i = 0; i < counter; i ++){
        if(input[i] % 2 == 0){
            printf("%d ", input[i]);
        }
    }
    printf("\n");

    return 0;
}
