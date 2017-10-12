#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    int number10 = 255;
    int newBase = 16;
    char buffer[100] = "";

    int digitPosition = 0;
    int number = number10;
	while (number > 0) {
        int newDigit = number % newBase;
        char newSymbol;
        if (newDigit <= 9) {
            newSymbol = '0' + newDigit;
        } else {
            newSymbol = 'a' + (newDigit - 10);
        }
        buffer[digitPosition] = newSymbol;
        digitPosition += 1;
        number = number / newBase;
    }
    buffer[digitPosition] = '\0';

    int length = digitPosition;
    for (int i = 0; i < length / 2; i++) {
        int tmp = buffer[i];
        buffer[i]  = buffer[length - 1 - i];
        buffer[length - 1 - i] = tmp;
    }

    printf("%i(10) --> %s(%i)\n", number10, buffer, newBase);

    return 0;
}