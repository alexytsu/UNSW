// COMP1521 18s1 Week 02 Lab (warm-up)

#include <stdio.h>

int main()
{
	// Code to generate and display the largest "int" value

	int x = ~0;
	printf("int %x, %d\n", x, x);

	// Code to generate and display the largest "unsigned int" value

	unsigned int y = ~0;
	printf("unsigned int %x, %d\n", y, y);

	// Code to generate and display the largest "long int" value

	long int xx = ~0;
	printf("long int %x, %d\n", xx, xx);

	// Code to generate and display the largest "unsigned long int" value

	unsigned long int xy = ~0;
	printf("unsigned long int %x, %d\n", xy, xy);

	// Code to generate and display the largest "long long int" value

	long long int xxx = ~0;
	printf("long long int %x, %d\n", xxx, xxx);

	// Code to generate and display the largest "unsigned long long int" value

	unsigned long long int xxy = ~0;
	printf("unsigned long long int %x, %d\n", xxy, xxy);

	return 0;
}

