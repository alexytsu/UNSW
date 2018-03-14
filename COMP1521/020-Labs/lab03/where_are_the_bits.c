// where_are_the_bits.c ... determine bit-field order
// COMP1521 Lab 03 Exercise
// Written by ...

#include <stdio.h>
#include <stdlib.h>

struct _bit_fields {
	unsigned int a : 4,
	b : 8,
	c : 20;
};

int main(void)
{
	struct _bit_fields x;

	printf("%u\n",sizeof(x));
	x.a = 0;
	x.b = 0;
	x.c = 1;

	printf("a: %d\n", x.a);
	printf("b: %d\n", x.b);
	printf("c: %d\n", x.c);

	void *a = &x;

	printf("the int %d\n", *(int *)a);

	x.a = 1;
	x.b = 0;
	x.c = 0;

	printf("a: %d\n", x.a);
	printf("b: %d\n", x.b);
	printf("c: %d\n", x.c);

	void *b = &x;

	printf("the int %d\n", *(int *)b);


	return 0;
}
