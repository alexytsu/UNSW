#include <stdio.h>
int main(void){
	int ch;
	int input[2000];
	int counter = 0;
	while((ch=getchar())!=EOF){
		input[counter] = ch;
		printf("%c", ch);
		counter++;	
	}
	
	printf("%d\n", counter);
	for(int i = 0; i < counter; i ++){
		printf("%c", input[i]);
	}
}
