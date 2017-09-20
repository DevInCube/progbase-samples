#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <progbase.h>
#include <progbase/console.h>

int main() { 
	Console_clear();

	int shiftY = 3;
	int shiftX = 20;
	int size = 10;
	
	for (int y = 0; y <= size; y++) {
		for (int x = 0; x <= size; x++) {
			if (x == y) {
				Console_setCursorAttribute(BG_RED);
			} else if (y == 0 || y == size 
				|| x == 0 || x == size) {
				Console_setCursorAttribute(BG_GREEN);
			} else if (x < y) {
				Console_setCursorAttribute(BG_WHITE);
			} else {
				Console_setCursorAttribute(BG_CYAN);
			}
			Console_setCursorPosition(shiftY + y, shiftX + x);
			putchar(' ');
		}
	}

	Console_reset();
	Console_setCursorPosition(15, 1);
	return 0; 
}
