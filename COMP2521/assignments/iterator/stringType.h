/* stringType.c ... 
   stringType interface/API 
   Written by Ashesh Mahidadia, August 2017
*/

#include <stdlib.h>
#include <stdio.h>

/* =====   stringType Functions for Generic interface/API ===== */

void  stringFree(void *vp);
void *stringNew(void const *vp);
int   stringCompare(void const *vp1, void const *vp2);

/* =====   End of stringType Functions for Generic interface/API ===== */
