#include <stdio.h>

int main() {
	char string[4096]; 

	printf("Enter a string: ");
	fgets(string, 4096, stdin);
	for(int i = 0; i < 4096; i++) {
		if(string[i] == '\n') break;
		printf("%c\n", string[i]);
	}
	return 0;
}