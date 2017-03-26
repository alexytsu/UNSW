#include <stdio.h>

int main(void){

    printf("Enter number: ");
    int number, i; 
    scanf("%d", &number);
    int sum = 0;  
    printf("The factors of %d are:\n", number);
    for(i = 1; i<=number; i++){
        if(number%i==0){
            printf("%d\n", i);
            sum += i;
        }
    }

    printf("Sum of factors = %d\n", sum);
    if(sum==number*2){
        printf("%d is a perfect number\n", number);
    }else{
        printf("%d is not a perfect number\n", number);
    }
}
