#include <stdio.h>

int main() {
	char string[4096];
	printf("Enter a string: ");
	fgets(string, 4096, stdin);

	int stringlength = 0;
	for(int i = 0; i < 4096; i++) {
		if(string[i] != '\n') {
			stringlength ++;
		}else{
			break;
		}
	}
	
	int isPalindrome = 1;
	for(int i = 0; i < stringlength; i ++){
		if(string[i] == string[stringlength-i-1]) {
		}else{
			isPalindrome = 0;
			break;
		}
	}

	if(isPalindrome){ 
		printf("String is a palindrome\n");
	}else{
		printf("String is not a palindrome\n");
	}
	return 0;
}