#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(void) {
    const int n = 20;
    char a[n];

    // fill array
    printf("Enter string: ");
    fgets(a, n, stdin);
    a[strlen(a) - 1] = '\0';
    puts(a);

    // modify array
    for (int i = 0; a[i] != '\0'; i++) {
        char c = a[i];
        if (isdigit(c)) {
            a[i] = '0' + ((c - '0') + 3) % 10;
        } else if (isalpha(c)) {
            a[i] = islower(c) ? toupper(c) : tolower(c);
        }
    }    

    puts("Modified array:");
    puts(a);
    
    return 0;
}