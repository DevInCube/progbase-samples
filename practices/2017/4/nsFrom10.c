#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <progbase.h>
#include <progbase/console.h>

int main() { 
	Console_clear();
	
	puts("ENter number:");
	int number = getInt();
	int base = 10;
	puts("ENter new base:");
	int newBase = getInt();

	printf("%i(%i) -> ___(%i)", number, base, newBase);

	int digitPosition = 0;
	while (number > 0) {
		int newDigit = number % newBase;

		Console_setCursorPosition(6, 40 - digitPosition);
		digitPosition += 1;
		printInt(newDigit);
		number = number / newBase;
	}
	
	Console_reset();
	Console_setCursorPosition(10, 1);
	puts("");
	return 0; 
}
