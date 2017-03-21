#include <stdio.h>

int main(void){
    
    int size;

    printf("Enter size: ");
    scanf("%d", &size);

    for(int x = 0; x < size; x += 1){
        for (int y = 0; y < size; y += 1){
            
            if(x==0){ //first row
                printf("*");
            }else if(y==0 && x!=1){ //leftmost side
                printf("*");
            }else if(x==size-1){ //bottom side
                printf("*");
            }else if(y==size-1){ //rightmost side
                printf("*");
            }else if(x%2==1 && x>=3){ //alternate lines beginning after the first
              
                if(x<= size/2){
                    if(y == x -3){
                        printf("*%d",x);
                    }else{
                        printf("-");
                    }
                }
                

            }
            else{
                printf("-");
            }

            if (y == size - 1){
                printf("\n");
            }
        }
    }

}
