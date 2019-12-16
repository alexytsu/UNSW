// COMP1521 18s1 Week 02 Lab (warm-up)

#include <stdio.h>

int main()
{
	// Code to generate and display the largest "int" value

	int x = ~0U >> 1;
	printf("int %x, %d\n", x, x);

	// Code to generate and display the largest "unsigned int" value

	unsigned int y = ~0;
	printf("unsigned int %x, %u\n", y, y);

	// Code to generate and display the largest "long int" value

	long int xx = ~0UL >> 1;
	printf("long int %lx, %ld\n", xx, xx);

	// Code to generate and display the largest "unsigned long int" value

	unsigned long int xy = ~0;
	printf("unsigned long int %lx, %lu\n", xy, xy);

	// Code to generate and display the largest "long long int" value

	long long int xxx = ~0ULL >> 1;
	printf("long long int %llx, %lld\n", xxx, xxx);

	// Code to generate and display the largest "unsigned long long int" value

	unsigned long long int xxy = ~0;
	printf("unsigned long long int %llx, %llu\n", xxy, xxy);

	return 0;
}

