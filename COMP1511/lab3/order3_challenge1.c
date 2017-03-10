#include <stdio.h>

int main(void){
    int a,b,c;
    printf("Enter integer: ");
    scanf("%d", &a);
    printf("Enter integer: ");
    scanf("%d", &b);
    printf("Enter integer: ");
    scanf("%d", &c);

    int avg,diff;
    avg = (a+b)/2;
    diff = (avg-a)%avg;
    a = avg-diff;
    b = avg+diff;

    avg = (b+c)/2;
    diff = (avg-b)%avg;
    b = avg-diff;
    c = avg+diff;

    avg = (a+b)/2;
    diff = (avg-a)%avg;
    a = avg-diff;
    b = avg+diff;
 
    printf("The integers in order are: %d %d %d", a,b,c);
}
