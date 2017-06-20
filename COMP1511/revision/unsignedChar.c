#include <stdio.h>

int main(void){

    typedef unsigned char byte;
    unsigned int nines = 999;
    byte * ptr = (byte *) &nines;

    printf ("%x\n",nines);
    printf ("%x\n",nines * 0x10);
    printf ("%d\n",ptr[0]);
    printf ("%d\n",ptr[1]);
    printf ("%d\n",ptr[2]);
    printf ("%d\n",ptr[3]);

}
