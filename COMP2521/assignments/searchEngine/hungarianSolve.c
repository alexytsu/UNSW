#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void generateHungarianMatrix(int size, double costMatrix[size][size])
{
}

void showMatrix(int size, double costMatrix[size][size]){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            printf("%.3lf ", costMatrix[i][j]);
        }            
        printf("\n");
    }

}
double findMinimum(int size, double costMatrix[size])
{
    double min = 1000000;
    for(int i = 0; i < size; i ++){
        if(costMatrix[i] < min)
            min = costMatrix[i];
    }
    return min;
}

void hungarianSolve(int urls, double costMatrix[urls][urls], int *resultVector)
{
    int size = urls;

    printf("ORIGINAL MATRIX\n");
    showMatrix(size, costMatrix);

    for(int i = 0; i < size; i ++){
        double min = findMinimum(size, costMatrix[i]);
        for(int j = 0; j < size; j ++){
            costMatrix[i][j] -= min;
        }
    }        

    printf("MATRIX AFTER ROW SUBTRACTION\n");
    showMatrix(size, costMatrix);

    double *columnMins = malloc(sizeof(double) * size);
    for(int i = 0; i < size; i++){
        columnMins[i] = 1000000; 
    }
    for(int i = 0; i < size; i ++){
        for(int j = 0; j < size; j++){  
            if(costMatrix[i][j] < columnMins[j]){
                columnMins[j] = costMatrix[i][j];
            }
        }
    }
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            costMatrix[i][j] -= columnMins[j];
        }            
    }
    printf("MATRIX AFTER COLUMN SUBTRACTION\n");
    showMatrix(size, costMatrix);

    //normalise zeros
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            costMatrix[i][j] = (costMatrix[i][j] > 10e-7) ? costMatrix[i][j]:0;
        }            
    }
}

int main(){

}

