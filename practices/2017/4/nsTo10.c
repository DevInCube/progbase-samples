#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <progbase.h>
#include <progbase/console.h>

int main() { 
	Console_clear();
	
	puts("ENter number:");
	int number = getInt();
	puts("ENter base:");
	int base = getInt();
	int newBase = 10;


	int digitPosition = 0;
	int d = number;
	int newNumber = 0;
	while (d > 0) {
		int newDigit = d % newBase;
		newNumber += newDigit * pow(base, digitPosition);
		digitPosition += 1;
		d = d / newBase;
	}

	printf("%i(%i) -> %i(%i)", number, base, newNumber, newBase);
	
	Console_reset();
	Console_setCursorPosition(10, 1);
	puts("");
	return 0; 
}
