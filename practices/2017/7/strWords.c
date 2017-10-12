#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(void) {
    const int n = 100;
    char a[n];
    char delimiter = ' ';
    
    strcpy(a, "a77asdh sdh sdjagdlasdgaksdg7qt ei12uegqweq98e1t2");

    int wordCounter = 0;
    char maxLengthWord[n];
    strcpy(maxLengthWord, "");
    char minLengthWord[n];
    strcpy(minLengthWord, a);

    char b[n];
    strcpy(b, "");
    int bindex = 0;
    for (int i = 0; i < strlen(a) + 1; i++) {
        if (isalpha(a[i])) {
            b[bindex] = a[i];
            bindex++;
        } else {
            if (bindex != 0) {
                b[bindex] = '\0';
                puts(b);
                bindex = 0;
                //
                wordCounter++;
                if (strlen(b) > strlen(maxLengthWord)) {
                    strcpy(maxLengthWord, b);
                }
                if (strlen(b) < strlen(minLengthWord)) {
                    strcpy(minLengthWord, b);
                }
            }
        }
    }
    puts("----------------------------");
    printf("count: %i\nmin: %s\nmax: %s\n", 
        wordCounter, minLengthWord, maxLengthWord);
    
    return 0;
}