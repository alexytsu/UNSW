#include <stdio.h>

int main(void){
    int a;
    int b = 1;
    printf("Enter size: ");
    scanf("%d", &a);
    while(b<=a*a){
        if(b%2==1){
            printf("*");
        }
        else{
            flip = 1;
        }
        if(b%a == 0){
           printf("\n");
        }
        b = b + 1;
    }

}
