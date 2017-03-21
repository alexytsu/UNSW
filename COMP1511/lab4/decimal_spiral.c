#include <stdio.h>

int main(void){
    int size, size2, counter, total;
    printf("Enter size: ");
    scanf("%d", &size);
    size2 = size - 1;

    //size2 is used to establish how many numbers will be in the spiral
    //total becomes the number of numbers in the spiral
    total = size2*3;
    size2 -= 2;
    while(size2 >= 2){
        total += 2*size2;
        size2 -= 2;
    }
    total += 1;
    //total is the length of the spiral
    //taking its modulus congruent to 10 will give us the starting digit
    counter = (total % 10) - 1;

    //size is the side length of the spiral
    //counter keeps the current digit 

    printf("counter: %d\n", counter);

    for(int x = 0; x < size; x += 1){
        for(int y = 0; y < size; y += 1){
            //while in the loop, we are at the coordinate (x,y)
            //where y gives the column and x gives the row

            //print the first line
            if(x == 0){
                printf("%d", counter);
                counter -= 1;
                total -= 1;
            }

            

            else{
                printf("-");
            }



        //print newline if at the end of the row
        if (y==size-1){
            printf("\n");
        }

        }
    }
}
