// BigNum.h ... LARGE positive integer values

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "BigNum.h"

int max(int a, int b) {
	return (a > b) ? a:b;
}

// Initialise a BigNum to N bytes, all zero
void initBigNum(BigNum *n, int Nbytes)
{
	n->nbytes = Nbytes;
	n->bytes= calloc(Nbytes, sizeof(Byte));
	assert(n->bytes != NULL);
	return;
}

// Add two BigNums and store result in a third BigNum
void addBigNums(BigNum n, BigNum m, BigNum *res)
{
	int length = max(n.nbytes, m.nbytes);
	length++;
	if(res->nbytes < length) {
		res->nbytes = length;
		free(res->bytes);
		res->bytes = calloc(length, sizeof(Byte));
	}

	int carryover = 0;

	int i;
	for(i = 0; i < length; i++){
		int mdigit = 0;
		int ndigit = 0;
		if(i < m.nbytes) mdigit = m.bytes[i];
		if(i < n.nbytes) ndigit = n.bytes[i];
		int result = (mdigit) + (ndigit);
		if(carryover) result++;
		carryover = (result > 10);
		res->bytes[i] = result % 10;
	}

	return;
}

// Set the value of a BigNum from a string of digits
// Returns 1 if it *was* a string of digits, 0 otherwise
int scanBigNum(char *s, BigNum *n)
{
	int length = strlen(s);
	int i = length - 1;
	int j = 0;

	int k;
	int first_space = -2;
	for(k = 0; k < length; k++){
		if(s[k] == ' ' && first_space == -2) continue;
		if(s[k] >= '0' && s[k] <= '9' && first_space < 0) first_space = -1;
		if(s[k] == ' ' && first_space == -1){
			first_space = 1;
			s[k] = '\0';
		}

	}

	length = strlen(s);

	while(s[j] == '0' || s[j] == ' '){
		j++;
		i--;
	}

	for(; i >= 0 && j<length; i--, j++){
		if(s[j] <= '9' && s[j] >= '0'){
			n->bytes[i] = s[j] - '0';
		}else{
			return 0;
		}

	}
	return 1;
}

// Display a BigNum in decimal format
void showBigNum(BigNum n)
{
    int i;
    int flag = 0;
    for(i = n.nbytes - 1; i >= 0; i--){
 		Byte curr = n.bytes[i];
 		if(flag == 0){
 			if(curr == 0){
 				continue;
 			}else{
 				flag = 1;
 				printf("%d", curr);
 			}
 		}else{
 			printf("%d", curr);
 		}
    }
	return;
}

