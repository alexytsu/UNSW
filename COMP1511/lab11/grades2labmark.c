#include <stdio.h>

double grades2labmark(char grades[]);

int main(int argc, char *argv[]){
    printf("%lf", grades2labmark(argv[1]));
    return 0;
}

double grades2labmark(char grades[]){
    double mark = 0;
    for(int i = 0; grades[i] != -1; i ++){
        switch (grades[i]){
            case 'A': mark+=1.0;
            case '+': mark+=0.2;
            case 'B': mark+=0.8;
            case 'C': mark+=0.5;
        }
    }
    return mark;
}

