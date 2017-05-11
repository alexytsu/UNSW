#include <stdio.h>
int main(){
	printf("Sum how many cubes? ");
	int cubes;
	scanf("%d", &cubes);
	int i,sum;
	sum = 0;
	for(i = 1; i <= cubes; i ++){
		printf("%d^3 ", i);
		if (i!=cubes){
			printf("+ ");
		}
		sum += i*i*i;
	}
	printf("= %d\n", sum);	
	return 0;
}
