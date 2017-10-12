#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

int main(void) {
    srand(time(0));

    const int n = 20;
    char a[n];

    // fill array
    for (int i = 0; i < n; i++) {
        switch (rand() % 3) {
            case 0: 
                a[i] = (rand() % ('z' - 'a' + 1)) + 'a';
                break;
            case 1:
                a[i] = (rand() % ('Z' - 'A' + 1)) + 'A';
                break;
            default:
                a[i] = (rand() % ('9' - '0' + 1)) + '0';
                break;
        }
    }

    for (int i = 0; i < n; i++) {
        putchar(a[i]);
    }    
    puts("");

    for (int i = 0; i < n; i++) {
        char c = a[i];
        if (isdigit(c)) {
            a[i] = '0' + ((c - '0') + 3) % 10;
        } else if (isalpha(c)) {
            a[i] = islower(c) ? toupper(c) : tolower(c);
        }
    }    

    puts("Modified array:");
    for (int i = 0; i < n; i++) {
        putchar(a[i]);
    }    
    puts("");
    
    return 0;
}