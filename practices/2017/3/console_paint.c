#include <stdio.h>
#include <progbase.h>
#include <progbase/console.h>

int main()
{
	Console_clear();

	Console_setCursorAttribute(BG_INTENSITY_BLUE);
	for (int x = 40; x <= 60; x = x + 1) {
		Console_setCursorPosition(5, x);
		putchar(' ');
		Console_setCursorPosition(10, x);
		putchar(' ');
	}

	Console_reset();
	Console_setCursorPosition(15, 1);
	return 0;
}
