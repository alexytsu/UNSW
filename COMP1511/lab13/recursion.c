#include <stdio.h>

int factorial(int n){
    int result;
    if(n==1){
        return 1;
    }
    result = factorial(n-1) *n;
    return result;
}

int main(void){
    printf("%d\n",factorial(100));
    return 0;
}
