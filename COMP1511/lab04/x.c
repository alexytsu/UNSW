#include <stdio.h>

int main(){
    int number = 0;
    printf("Enter size: ");
    scanf("%d", &number);

    for(int x = 0; x < number; x ++){
        for(int y = 0; y < number; y ++){
            if(x==y || number-y-1==x){
                printf("*");
            }else{
                printf("-");
            }
        }
        printf("\n");
    }
}
