#include <stdio.h>
#define MAX_LINE 1024

int main(int argc, char *argv[]){

    char *filename = argv[1];
    FILE *fp;
    FILE *fin;
    fp = fopen(filename, "r");

    char buffer[10][MAX_LINE];
    for(int i = 0; i < 10; i ++){
        buffer[i][0] = -1;
    }
    char cur_line[MAX_LINE];
    int lines = 0;

    while(fscanf(fp, "%s", cur_line)!=EOF){
        lines ++; 
        /*
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
        */
    }

    fclose(fp);
    fin = fopen(filename, "r");
    while(fscanf(fin, "%s", cur_line)!=EOF){
        if(lines<=10){
            for(int i = 0; i < MAX_LINE; i ++){
                buffer[lines-1][i] = cur_line[i];
            }
        }
        lines--;
    }

    fclose(fin);

    for(int i = 0; i < 10; i ++){
        if(buffer[i][0] != -1){
            printf("%s\n", buffer[9-j]);
        }
    }


    return 0;
}
