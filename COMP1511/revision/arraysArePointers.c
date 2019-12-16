#include <stdio.h>

int main(int argc, char *argv[]){

    char s[] = "Hi!";
    printf("s:\t%p\t*s:\t%c\n\n", s, *s);
    printf("&s[0]:\t%p\ts[0]:\t%c\n", &s[0], s[0]);
    printf("&s[1]:\t%p\ts[1]:\t%c\n", &s[1], s[1]);
    printf("&s[2]:\t%p\ts[2]:\t%c\n", &s[2], s[2]);
    printf("&s[3]:\t%p\ts[3]:\t%c\n", &s[3], s[3]);

    return 0;
}
