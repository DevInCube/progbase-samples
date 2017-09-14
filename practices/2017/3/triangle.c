#include <stdio.h>
#include <math.h>
#include <progbase.h>

int main()
{
	int a = 0;
	int b = 0;
	int c = 0;
	puts("Enter a:");
	a = getInt();
	puts("Enter b:");
	b = getInt();
	puts("Enter c:");
	c = getInt();

	if (a <= 0 || b <= 0 || c <= 0) {
		puts("Invalid value (<= 0)");
	} else {
		if (a + b < c || b + c < a || a + c < b) {
			puts("Doesn't exist");
		} else if (a == b && b == c) {
			puts("All equals");
		} else if (a == b || a == c || b == c) {
			puts("Two equals");
		} else {
			puts("Custom");
		}
	}
	return 0;
}
