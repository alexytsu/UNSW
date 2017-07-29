#include <stdio.h>
#include <stdlib.h>

int factorial(int input);

int main(int argc, char *argv[]){
        int input = atoi(argv[1]);
        printf("%d\n", factorial(input));
        return 0;
}

int factorial(int input){
        return (input > 1) ? factorial(input-1) * input: 1;
}
