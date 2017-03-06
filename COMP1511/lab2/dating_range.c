#include <stdio.h>

int main(void){
    int age, low, high;
    printf("Enter your age: ");
    scanf("%d", &age);
    low = age/2 + 7;
    high = age+2*(age-low);
    if(low>=high){
        printf("You are too young to be dating.\n");
    }else{
        printf("Your dating range is %d to %d years old.\n", low, high);
    }
    return(0);
}
