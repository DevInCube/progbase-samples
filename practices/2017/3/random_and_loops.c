#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <progbase.h>

int main()
{
	srand(time(0)); // init randomizer
	int sum = 0;
	int min = 50;
	int max = -50;
	for (int i = 0; i < 10; i = i + 1)
	{
		int x = rand() % (100 + 1) - 50;
		if (x < min) {
			min = x;
		}
		if (x > max) {
			max = x;
		}
		sum = sum + x;
		printInt(x);
		printf(", ");
	}
	puts("Sum is:");
	printInt(sum);
	puts("");
	puts("Min is:");
	printInt(min);
	puts("");
	puts("Max is:");
	printInt(max);
	puts("");
	return 0;
}
