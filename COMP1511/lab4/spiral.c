#include <stdio.h>

int main(void){

    //Get the size parameter from the user
    int size;
    printf("Enter size: ");
    scanf("%d", &size);
    int midrow = (size-1)/2; 
    //These nested loops will print through the entire grid
    //with x corresponding to the row and y corresponding to the column
	int x,y;
    for(x = 1; x <= size; x += 1){
        for (y = 1; y <= size; y += 1){
			int j;
            //here are conditions under which, it will always be an asterix
            //top row, right border, bottom row, left border(excl row2)
            if(x==1 || y==size || x==size || y==1&&x!=2&&x%2!=0&&(x%2==0)){
                printf("*");
            }

            //even lines before midline
            else if(x%2==0 && x <= midrow){

                int stars = x - 1;
                int starsprinted = 0;
                //j counts the columns in this even line
                for(j = 1; j<=size; j += 1){
                    if(starsprinted < stars/2 && j%2==1){
                        printf("*");
                        starsprinted += 1;
                    }else if(starsprinted >= stars/2 && j%2==1){
                        int yettoprint = stars - starsprinted;
                        if((size-j)/2<yettoprint){
                            printf("*");
                            starsprinted += 1;
                        }else{
                            printf("-");
                        }
                    }
                    else{
                        printf("-");
                    }
                }
                y += size;
            }

            //odd lines before midline
            else if(x%2==1 && x<= midrow){
                int dashes = x - 2;
                int dashesprinted = 0;
                //j counts the columns in this odd line
                for(j = 1; j<=size; j += 1){
                    if(dashesprinted < dashes/2 && j%2==0){
                        printf("-");
                        dashesprinted += 1;
                    }else if(dashesprinted >= dashes/2 && j%2==0){
                        int yettoprint = dashes - dashesprinted;
                        if((size-j)/2 + 1 <= yettoprint){
                            printf("-");
                            dashesprinted += 1;
                        }else{
                            printf("*");
                        }
                    }else{
                        if(j!=2){
                        printf("*");
                        }
                    }
                }
                y += size;
            }

            //odd lines after midline
			else if (x%2==1){
				int dashes = size - x;
				int dashesprinted = 0;
				//j counts the columns in this odd line
				for(j =1; j<=size; j+=1){
					if(dashesprinted <= dashes/2 && j%2==0){
						printf("-");
						dashesprinted += 1;
					}else if(dashesprinted > dashes/2 && j%2==0){
						int yettoprint = dashes - dashesprinted;
						if((size-j)/2 + 1 <= yettoprint){
							printf("-");
							dashesprinted += 1;
						}else{
							printf("*");
						}
					}else{
						printf("*");
					}
				}
				y += size;
			}

            //even lines after midline
            else if(x%2==0){
                int stars = size - x + 1;
                int starsprinted = 0;
                for(j = 1; j<=size; j += 1){
                    if(starsprinted < stars/2 && j%2==1){
                        printf("*");
                        starsprinted += 1;
                    }else if(starsprinted >= stars/2 && j%2==1){
                        int yettoprint = stars - starsprinted;
                        if((size-j)/2<yettoprint){
                            printf("*");
                            starsprinted += 1;
                        }else{
                            printf("-");
                        }
                    }
                    else{
                        printf("-");
                    }
                }
                    y += size;
            }

            //if not an asterix, print a blank
            else{
                printf("-");
            }
        }
    //at the end of each row, print a newline
    printf("\n");
    }
}
