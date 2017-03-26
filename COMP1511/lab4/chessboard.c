#include <stdio.h>

int main(void){
    int a;
    int b = 1;
    int flip = 0;
    printf("Enter size: ");
    scanf("%d", &a);
    while(b<=a*a){
        if(flip){
            printf("*");
            flip = 0;
        }
        else{
            flip = 1;
            printf("-");
        }
        if(b%a == 0){
           printf("\n");
        }
        b = b + 1;
    }

}
