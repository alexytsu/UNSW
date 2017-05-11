#include <stdio.h>

int main(void){
    int number, row, column;
    printf("Enter size: ");
    scanf("%d", &number);
    row=1;
    while (row<=number && row<=number/2+1) {
        column=1;
        while (column <= number){
            if(column <= number - row + 1 && row%2 != 0 && column >= row-2){
                printf("*");
            } else if (column <= number - row + 1 && row%2==0 && column >=  row -2){
                printf("-");
            } else if (column%2!=0){
                printf("*");
            } else{
                printf("-");
            }
            column=column+1;
        }
        printf("\n");
        row=row+1;
    }
    while (row<=number && row>=number/2+1){
        column=1;
        while(column<=number) {
            if (column>=number-row+1 && row%2!=0 && column<=row-1){
                printf("*");
            } else if (column>=number -row +1 && row%2==0 && column <= row -1){
                printf("-");
            } else if (column%2!=0){
                printf("*"); 
            } else{
                printf("-");
            }
            column=column+1;
        }
        printf("\n");
        row=row+1;
    }
    return 0;

}
