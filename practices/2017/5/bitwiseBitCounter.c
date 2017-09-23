#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	int n = 1;
	int counter = 0;
	int bitsNumber = sizeof(n) * 8;

	for (int i = 0; i < bitsNumber; i++) {
		if ((n & 1) == 1) {
			counter = counter + 1;
		}
		n = n >> 1;
	}

	printf("Count = %i \n", counter);

	return 0;
}
