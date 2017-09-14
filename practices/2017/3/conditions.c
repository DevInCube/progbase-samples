#include <stdio.h>
#include <math.h>
#include <progbase.h>

#define PI 3.14

int main()
{
	float x = 0;
	float y = 0;
	float z = 0;

	puts("Enter x:");
	x = getFloat(); 
	puts("Enter y:");
	y = getFloat(); 
	if (fabs(y) > 0.00001)
	{
		puts("Division by zero (y)");
	}
	else
	{
		puts("Enter z:");
		z = getFloat();
		if (fabs(z) < 0.00001)
		{
			puts("Division by zero (z)");
		}
		else
		{
			float u = (x * sin(PI / z)) / y;
			// @todo check u negative
			float result = sqrt(u);
			puts("This is result: ");
			printFloat(result);
			puts("");
		}
	}
	return 0;
}
