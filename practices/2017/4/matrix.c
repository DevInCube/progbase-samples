#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <progbase.h>
#include <progbase/console.h>

int main() { 
	Console_clear();
	srand(time(0));

	int minRandValue = -5;
	int maxRandValue = 5;
	int width = 10;
	int sum = 0;
	for (int i = 0; i < width * width; i++) {
		int x = i % width;
		int y = i / width;
		int number = (rand() % (maxRandValue - minRandValue + 1)) 
			+ minRandValue;
		if (i % width == 0) {
			puts("");
		}
		if (x == y) {
			Console_setCursorAttribute(BG_INTENSITY_YELLOW);
			printf("   * ");
		} else if (y == -x + width - 1) {
			Console_setCursorAttribute(BG_INTENSITY_MAGENTA);
			printf("   # ");
		} else if (y < -x + width - 1) {
			Console_setCursorAttribute(BG_DEFAULT);
			printf("     ");
		} else {
			Console_setCursorAttribute(BG_INTENSITY_CYAN);
			printf("%4i ", number);
		}
		if (x == y) {
			sum += number;
		}
	}
	Console_setCursorAttribute(BG_DEFAULT);
	puts("");
	puts("Sum:");
	printInt(sum);

	puts("");
	return 0; 
}
