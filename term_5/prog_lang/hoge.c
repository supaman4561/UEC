#include <stdio.h>

int main(void)
{
	char c1, c2;

	c1 = 'A';
	c2 = 'B';

	if (c1 > c2) {
		printf("c1 > c2\n");
	} else {
		printf("c1 < c2\n");
	}

	return 0;
}
