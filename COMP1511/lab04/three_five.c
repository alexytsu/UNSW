#include <stdio.h>

int main(void){

    printf("Enter number: ");
    int number, i; 
    scanf("%d", &number);

    for(i = 3; i<number; i++){
        if(i%3==0||i%5==0){
            printf("%d\n", i);
        }
    }

}
