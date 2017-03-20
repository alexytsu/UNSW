#include <stdio.h>
int main(){
	printf("Enter how many cubes: ");
	int cubes;
	scanf("%d", &cubes);
	int i;
	for(i = 1; i <= cubes; i ++){
		printf("%d^3 = %d\n", i, i*i*i);
	}
	return 0;
}
