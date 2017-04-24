#include <stdio.h>
#include "captcha.h"

int decide_digit(double h_balance, double v_balance, double density, int
        holes, double quadrant_densities[4]){
    
    //the easiest branch to analyse first is holes as it reliably splits
    //digits into three distinct categories
    if(holes == 2){
        return 8;
    }else if(holes == 1){
        //the number is either a 6 or 9 or 0

        //let's test if it's a 0
        double min_dens = 1, max_dens = 0;
        int min_dens_quad = 0, max_dens_quad = 0;
        for(int i = 0; i < 4; i++){
            if(quadrant_densities[i] <= min_dens){
                min_dens = quadrant_densities[i];
                min_dens_quad = i;
            }
            if(quadrant_densities[i] >= max_dens){
                max_dens = quadrant_densities[i];
                max_dens_quad = i;
            }
        }
        if(max_dens - min_dens >= 0.2){
            if(min_dens_quad == 0){
                return 9;
            }else if(min_dens_quad == 3){
                return 6;
            }
        }else{
            if(h_balance >= 0.5 && v_balance >= 0.5){
                return 9;
            }else{
                return 6;
            }
        }

    }
    return 0;
}
