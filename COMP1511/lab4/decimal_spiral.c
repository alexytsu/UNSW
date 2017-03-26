#include <stdio.h>

int getDecimal(int s, int l, int x, int y);

int main(void){

    //get size of grid from user
    /*
    int size; 
    printf("Enter size: ");
    scanf("%d", &size);
    */

    //while testing, set grid to a value
    int size = 9;
    //get the length of the spiral from the size of the grid
    int length = size * 2;
    int s = size - 2;
    while(s >= 2){
        length += 2 * s;
        s -= 2;
    }
    printf("%d\n", length);
    //assuming the spiral starts at 0
    //from the outside in, the digit should be
    //(length - posSpiral) % 10 
    //print the grid
    //for each coordinate value, we will check 
    //if it lies on the spiral
    //and if it does, how far along the spiral it is 

    int row, col;
    int onSpiral, posSpiral;

    //print the top half
    for(row = 1; row <= size/2+1; row++){
        for(col = 1; col <= size; col++){
            if(col <= size - row + 1 && row%2 != 0 && col >= row-2){
                //printf("+");
                printf("%d", getDecimal(size, length, row, col));
            } else if (col <= size - row + 1 && row%2==0 && col >=  row -2){
                printf("-");
            } else if (col%2!=0){
                //printf("*");
                printf("%d", getDecimal(size, length, row, col));
            } else{
                printf("-");
            }
        }//closes col loop
       printf("\n"); 
    }//closes row loop

    //print lower half
    for(row = size/2+2; row <= size; row++){
        for(col = 1; col <= size; col++){
            if (col>=size-row+1 && row%2!=0 && col<=row-1){
                //printf("*");
                printf("%d", getDecimal(size, length, row, col));
            } else if (col>=size -row +1 && row%2==0 && col <= row -1){
                printf("-");
            } else if (col%2!=0){
                //printf("*");
                printf("%d", getDecimal(size, length, row, col));
            } else{
                printf("-");
            }
        }//closes col loop
       printf("\n"); 
    }//closes row loop
}



int getDecimal(int s, int l, int xpos, int ypos){

    int x = 1;
    int y = 1;
    int travelledTotal = 0 ;
    int curSide = s;
    int curTravelled = 0;
    int dir = 0;
    int sideTime = 0;
    int secondTime = 0;

    while( (x != xpos) || (y != ypos)){
        curTravelled += 1;
        if(curTravelled < curSide ){
            if(dir%4==0){
                y+=1;
                travelledTotal += 1;
            }else if (dir%4==1){
                x+=1;
                travelledTotal += 1;
            }else if (dir%4==2){
                y-=1;
                travelledTotal += 1;
            }else if (dir%4==3){
                x-=1;
                travelledTotal += 1;
            }
        }


        else if(curTravelled == curSide){
            //change direction
            dir ++;
            curTravelled = 0;
            printf("curTravelled: %d curSide: %d\n", curTravelled, curSide); 
            if (curSide == s){
                sideTime ++;
                if (sideTime == 3){
                    curSide -= 2;
                }
            
            }else if(secondTime){
                curSide -= 2;
                secondTime = 0;
            }else{
                secondTime = 1;
            }
            
            printf("curTravelled: %d curSide: %d\n", curTravelled, curSide); 
        }
        
    
    }
    /*if (x == 1){
        return (l - (y - 1)) % 10;
    }else if (y == s){
        return (l - (y - 1 + x - 1)) % 10;
    }else if(x == s + 1){
        return (l + (y - 1 + x - 1)) % 10;
    }else if(y ==1 ){
        return (l - (y  - x )) % 10;     
    }else{
        return 0;
    }*/
    //s is (side length of the grid
    //l is the length of the spiral
    return (l - travelledTotal - 1)%10;
    //x and y give the position of the coordinate 
}
