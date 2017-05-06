#include <stdio.h>
#define MAX_LINE 1024

int main(int argc, char *argv[]){

    char *filename = argv[1];
    FILE *fp;
    fp = fopen(filename, "r");

    char buffer[10][MAX_LINE];
    char cur_line[MAX_LINE];
    int lines = 0;
    while(fscanf(fp, "%s", cur_line)!=EOF){
        lines ++; 
        for(int i = 0; i < MAX_LINE; i ++){

            buffer[9][i] = buffer[8][i];
            buffer[8][i] = buffer[7][i];
            buffer[7][i] = buffer[6][i];
            buffer[6][i] = buffer[5][i];
            buffer[5][i] = buffer[4][i];
            buffer[4][i] = buffer[3][i];
            buffer[3][i] = buffer[2][i];
            buffer[2][i] = buffer[1][i];
            buffer[1][i] = buffer[0][i];
            buffer[0][i] = cur_line[i];
        }
    }
    fclose(fp);

    if(lines >= 10){
        for(int i = 0; i < 10; i ++){
            printf("%s\n", buffer[9 - i]);
        }
    }else{
        int starting_index = lines - 1;
        for(int i = starting_index; i >= 0; i ++){
            printf("%s\n", buffer[i]);
        }
    }

    return 0;
}
