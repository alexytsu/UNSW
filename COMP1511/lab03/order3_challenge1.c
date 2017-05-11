#include <stdio.h>

int main(void){
    int a,b,c;
    printf("Enter integer: ");
    scanf("%d", &a);
    printf("Enter integer: ");
    scanf("%d", &b);
    printf("Enter integer: ");
    scanf("%d", &c);


    int avg,diff,factor;
    avg = (a+b);
    diff = (avg-2*a)%avg;
    factor = -1;
    factor = factor + 2*(b>a);
    diff = diff*factor;
    a = (avg-diff)/2;
    b = (avg+diff)/2;

    avg = (b+c);
    diff = (avg-2*b)%avg;
    factor = -1;
    factor = factor + 2*(c>b);
    diff = diff*factor;
    b = (avg-diff)/2;
    c = (avg+diff)/2;
    


    
    avg = (a+b);
    diff = (avg-2*a)%avg;
    factor = -1;
    factor = factor + 2*(b>a);
    diff = diff*factor;
    a = (avg-diff)/2;
    b = (avg+diff)/2;
   
    printf("The integers in order are: %d %d %d\n" ,a,b,c);

}
