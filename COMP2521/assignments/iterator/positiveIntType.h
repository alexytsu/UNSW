/* positiveIntType.h ... 
   positiveIntType interface/API 
   Written by Ashesh Mahidadia, August 2017
*/

#include <stdlib.h>
#include <stdio.h>


/* =====   positiveIntType Functions for Generic interface/API ===== */

void  positiveIntFree(void *vp);
void *positiveIntNew(void const *vp);
int   positiveIntCompare(void const *vp1, void const *vp2);

/* =====   End of positiveIntType Functions for Generic interface/API ===== */
