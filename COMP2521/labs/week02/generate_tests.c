#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printError(int n){
	printf("%d\n", n);
}
int main()
{
	FILE *fin = fopen("results.txt", "r");
	char buffer[100];

	//throwaway garbage files
	for(int i = 0; i < 7; i++){ 
		fgets(buffer, 100, fin);
	}

	int alternate = 1;
	double time = 0;

	typedef struct data{
		double t1;
		double t2;
		double t3;
		double average;
	}Data;

	int sort_types = 2;
	int test_sizes = 5;
	int list_styles = 6;
	Data timings[sort_types][test_sizes][list_styles];
	for(int i = 0; i < 2; i ++){
		for(int j = 0; j < 5; j ++){
			for(int k = 0; k < 6; k ++){
				timings[i][j][k].average = 0;
			}
		}
	}

	while(fgets(buffer, 100, fin) != NULL){
		if(alternate){
			if(sscanf(buffer, "%lf", &time)==0){
				fprintf(stderr, "Error reading line from results.txt\n");
			}
		}else{
			char which_sort[20];
			char style[20];
			int n;
			char trash[10];
			int trial;
			sscanf(buffer, "%s %s %d %s %d", which_sort, style, &n, trash, &trial);

			int sort_type = (strcmp(which_sort, "UNIX_SORT") == 0) ? 0:1;
			int style_index;
			if(strcmp(style, "reversed")==0){
				style_index = 0;
			}else if(strcmp(style, "random") == 0){
				style_index = 1;
			}else if(strcmp(style, "sorted") == 0){
				style_index = 2;
			}else if(strcmp(style, "random_dup") == 0){
				style_index = 3;
			}else if(strcmp(style, "reversed_dup") == 0){
				style_index = 4;
			}else if(strcmp(style, "sorted_dup") == 0){
				style_index = 5;
			}else{
				printError(0);
				return 1;
			}
			int size_index;
			switch(n){
			case 10000:
				size_index = 0;
				break;
			case 25000:
				size_index = 1;
				break;
			case 50000:
				size_index = 2;
				break;
			case 100000:
				size_index = 3;
				break;
			case 110000:
				size_index = 4;
				break;
			default:
				printError(1);
				return 1;
			}

			//Data timings[sort_types][test_sizes][list_styles];
			if(trial == 0){
				timings[sort_type][size_index][style_index].t1 = time;
				timings[sort_type][size_index][style_index].average += time;
			}else if(trial == 1){
				timings[sort_type][size_index][style_index].t2 = time;
				timings[sort_type][size_index][style_index].average += time;
			}else if(trial == 2){
				timings[sort_type][size_index][style_index].t3 = time;
				timings[sort_type][size_index][style_index].average += time;
			}else{
				printError(2);
				return 1;
			}

			//printf("%s %s %d %s %d:\t %lf\n", which_sort, style, n, trash, trial, time);
		}
		alternate = (alternate) ? 0:1;

	}

	char style[20];
	int test_size;

	printf("Sort Algorithm\t Size\t Style_(?with dupes)\t t1\t t2\t t3\t tavg\n");
	for(int i = 0; i < 6; i ++){
		for(int j = 0; j < 5; j ++){
			switch (i){
			case 0:
				strcpy(style, "reversed");
				break;
			case 1:
				strcpy(style, "random    ");
				break;
			case 2:
				strcpy(style, "sorted   ");
				break;
			case 3:
				strcpy(style, "random_dup");
				break;
			case 4:
				strcpy(style, "reversed_dup");
				break;
			case 5:
				strcpy(style, "sorted_dup");
				break;
			default:
				printError(3);
				return 1;
			}
			switch (j){
			case 0:
				test_size = 10000;
				break;
			case 1:
				test_size = 25000;
				break;
			case 2:
				test_size = 50000;
				break;
			case 3:
				test_size = 100000;
				break;
			case 4:
				test_size = 110000;
				break;
			default:
				printError(4);
				return 1;
			}
			printf("\n");
			printf("UNIX_SORT\t %d\t %s\t %lf\t %lf\t %lf\t %lf\n", test_size, style, timings[0][j][i].t1, timings[0][j][i].t2, timings[0][j][i].t3, timings[0][j][i].average/3);
			printf("INSERT_SORT\t %d\t %s\t %lf\t %lf\t %lf\t %lf\n", test_size, style, timings[1][j][i].t1, timings[1][j][i].t2, timings[1][j][i].t3, timings[1][j][i].average/3);
		}
	}
}
