#include <stdio.h>

int main(void){

    int a,b,c;
    printf("Enter integer: ");
    scanf("%d", &a);
    printf("Enter integer: ");
    scanf("%d", &b);
    printf("Enter integer: ");
    scanf("%d", &c);

    printf("The integers in order are: %d %d %d\n" ,
        a*(a<b && a<c) + b*(b<a && b<c) + c*(c<a && c<b),
        a*((a<b && a>c)||(a<c && a>b)) + b*((b<c && b>a)||(b>c && b<a)) + c*((c<a && c>b)||(c>a && c<b)),
        a*(a>b && a>c) + b*(b>c&&b>a) + c*(c>a&&c>b));

}
