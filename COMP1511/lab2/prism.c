#include <stdio.h>

int main(void) {
    int length, width, height;
    printf("Please enter prism length: ");
    scanf("%d", &length); 
    printf("Please enter prism width: ");
    scanf("%d", &width); 
    printf("Please enter prism height: ");
    scanf("%d", &height); 
    printf("A prism with sides %d %d %d has:\n", width, length, height);
    printf("Volume = %d\n", width*height*length);
    printf("Area = %d\n", 2*(width*height+height*length+width*length));
    printf("Edge length = %d\n", 4*(width+height+length));
    return(0); 
}
    
