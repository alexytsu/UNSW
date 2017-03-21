#include <stdio.h>

int main(void){

    printf("Enter number: ");
    int number, isPrime;
    isPrime = 1;
    scanf("%d", &number);
    int pusheen = number;
    int factor = 2;

    for(int i = 2; i < number/2; i += 1){
        if(number % i == 0){
            isPrime = 0;
            break;
        }
    }

    if(isPrime){
        printf("%d is prime\n", number);
    }
    else{
        printf("The prime factorization of %d is:\n", number);
        while(factor <= number){
            if(number%factor == 0){
                number = number/factor;
                printf("%d", factor);
                if(number!=1){
                    printf(" * ");
                }
            }else{
                factor += 1;
            }
        } 
        printf(" = %d\n", pusheen);
    }
}
