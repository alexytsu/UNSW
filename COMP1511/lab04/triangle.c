#include <stdio.h>

int main(void){
    int size;
    printf("Enter number: ");
    scanf("%d", &size);

    int i,j;

    for(i = 0; i<size; i++){
        for(j = 0; j<size; j++){
            if(j>=size-i-1){
                printf("*");
            }else{
                printf("-");
            }
        }
        printf("\n");
    }
}
