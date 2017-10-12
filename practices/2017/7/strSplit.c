#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(void) {
    const int n = 100;
    char a[n];
    char delimiter = ' ';
    
    strcpy(a, "asdh sdh sdjagdlasdgaksdg7qt ei12uegqweq98e1t2");
    char b[n];
    strcpy(b, "");
    int bindex = 0;
    for (int i = 0; i < strlen(a) + 1; i++) {
        if (a[i] == delimiter || a[i] == '\0') {
            b[bindex] = '\0';
            puts(b);
            bindex = 0;
        } else {
            b[bindex] = a[i];
            bindex++;
        }
    }
    
    return 0;
}