#include <stdio.h>
#include <ctype.h>

int main() {
	char string[4096];
	char newString[4096];
	printf("Enter a string: ");
	fgets(string, 4096, stdin);

	int stringlength = 0, counter = 0, isPalindrome = 1;

	for(int i = 0; i < 4096; i++) {
		if(string[i] == '\n') {
			break;
		}
		if((string[i] >= 'a' && string[i] <= 'z') || (string[i] >= 'A' && string[i] <= 'Z')) {
			newString[counter] = string[i]; 
			counter = counter + 1;
			
		}
	}
	
	//idk why it didnt work in the above loop
	for(int i = 0; i < counter; i++) {
		newString[i] = tolower(newString[i]);
	}

	for(int i = 0; i < counter; i ++){
		if(newString[i] == newString[counter-i-1]) {
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

	//printf("%s\n", newString);
	return 0;
}