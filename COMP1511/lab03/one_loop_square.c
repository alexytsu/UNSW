#include <stdio.h>

int main(void){
    int a;
    int b = 1;
    printf("Square size: ");
    scanf("%d", &a);
    while(b<=a*a){
       printf("*");
       if(b%a == 0){
           printf("\n");
       }
       b = b + 1;
    }

}
