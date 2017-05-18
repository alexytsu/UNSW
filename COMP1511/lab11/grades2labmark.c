#include <stdio.h>

double grades2labmark(char grades[]);

int main(int argc, char *argv[]){
    printf("%.1lf\n", grades2labmark(argv[1]));
    return 0;
}

double grades2labmark(char grades[]){
    double mark = 0;

    for(int i = 0; grades[i] != NULL; i ++){
        switch (grades[i]){
            case 'A': 
                mark+=1.0;
                break;
            case '+': 
                mark+=0.2;
                break;
            case 'B': 
                mark+=0.8;
                break;
            case 'C':
                mark+=0.5;
                break;
        }
    }
    if(mark > 10) return 10.0;
    return mark;
}

