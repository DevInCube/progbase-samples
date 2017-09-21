#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	int N = 0;
	int M = 0;

	puts("Enter N:");
	scanf("%i", &N);
	puts("Enter M:");
	scanf("%i", &M);
	printf("N = %i, M = %i\n", N, M);

	if (N <= 0 || M <= 0)
	{
		puts("negative values not allowed here!");
	}
	else if (N >= M)
	{
		puts("N should be less that M");
	}
	else
	{
		int sum = 0;

		for (int i = N; i <= M; i++)
		{
			sum += i;
		}

		printf("Sum = %i\n", sum);
	}
	return 0;
}
