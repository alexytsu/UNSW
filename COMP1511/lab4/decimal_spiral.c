#include <stdio.h>

int main(void){
    int size, size2, counter, total;
    printf("Enter size: ");
    scanf("%d", &size);
    size2 = size - 1;
    total = size2*3;
    size2 -= 2;
    while(size2 >= 2){
        total += 2*size2;
        size2 -= 2;
    }
    total += 1;
    printf("%d\n", total);
    counter = (total%10)-1;
    printf("%d\n", counter);
    for(int x = 0; x < size; x += 1){
        for(int y = 0; y < size; y += 1){
            printf("-");
            if (y==size-1){
                printf("\n");
            }
        }
    }
}
