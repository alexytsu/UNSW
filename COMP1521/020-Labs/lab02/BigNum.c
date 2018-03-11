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
		assert(res->bytes != NULL);
	}

	int carryover = 0;

	int i;
	for(i = 0; i < length; i++){
		int mdigit = 0;
		int ndigit = 0;
		if(i < m.nbytes) mdigit = m.bytes[i];
		if(i < n.nbytes) ndigit = n.bytes[i];
		int result = mdigit + ndigit + carryover;
		carryover = (result/10);
		res->bytes[i] = result % 10;
	}

	return;
}

// Set the value of a BigNum from a string of digits
// Returns 1 if it *was* a string of digits, 0 otherwise
int scanBigNum(char *s, BigNum *n)
{

	while(*s == '0' || *s == ' '){
		s++;
		if(*s == '\0') return 0;
	}

	int s_len = strlen(s);
	int i;
	for(i = s_len - 1; i >= 0; i--) {
		if(s[i] != ' ') break;
	}
	s[++i] = 0;

	s_len = strlen(s);
	if(s_len >= n->nbytes) {
		n->nbytes = s_len;
		free(n->bytes);
		n->bytes = calloc(s_len, sizeof(Byte));
		assert(n->bytes != NULL);
	}

	int j = 0;
	for(i = s_len - 1; i >=0; i--, j++) {
		if(s[i] >= '0' && s[i] <= '9') n->bytes[j] = s[i] - '0';
		else return 0;
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

