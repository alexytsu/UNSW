# Tutorial 7/3/17 

## Bracket Matching Algorithm 

This uses stacks to match and check the validity of a string with stacks.

```c
#include <stdio.h>
#include "Stack.h"

int main() {

    int c;
    Stack s;
    initStack(&s);

    while((c = getc()) != EOF) {
        if((c == '(' || c == '[' || c == '{')) {
            if(!pushStack(&s, c)) {
                fprintf(stderr, "Stack is full.\n");
                return 1;
            }
            else if(c == ']' && popStack(&s) != '[') {
                fprintf(stederr, "Mismatch\n");
            } 
            else if(c == '}' && popStack(&s) != '{') {
                fprintf(stederr, "Mismatch\n");
            } 
            else if(c == ')' && popStack(&s) != '(') {
                fprintf(stederr, "Mismatch\n");
            } 
        }
    }

    if(!isEmptyStack(&s)) {
        fprintf(sderr, "Not all brackets were closed\n");
    }

    printf("Matched!\n");
    return 0;
}
```
