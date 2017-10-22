//code taken from http://www.sanfoundry.com/c-program-implement-heap-algorithm-permutation-n-numbers/  
    #include <stdio.h>
    #include <stdlib.h>
	#include "perms.h"
	#include "setRank.h"
    #include "ratioList.h"
    void permSwap (int *x, int *y){
        int temp;
        temp = *x;
        *x = *y;
        *y = temp;
    }

    double heappermute(Set s, Set *final, List l, int v[], int n, int minFootRank, int endSize) {
        int i;
        double indivScaledFoot = 0;
        if (n == 1) {
            return minFootRank;
    	}

        else {
            for(i = 0; i < n; i++) {
                if(n % 2 == 1) {
                    permSwap(&v[0], &v[n-1]);
    	   		 }else{
                    permSwap(&v[i], &v[n-1]);
                 }
            }

        	insertPRank(s, v);	//assigns the permutated pRank to all elms in set

            indivScaledFoot = findScaled(l, s, endSize);
            if(minFootRank==0||indivScaledFoot<minFootRank){

                 minFootRank = indivScaledFoot;

                 insertPRank(*final, v);

            }
            minFootRank = heappermute(s, final, l, v, n-1, minFootRank, endSize);
        }
        return minFootRank;
    }     
