#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    
    const int height = 10;
    const int length = 100;
    char str[length];
    char buf[height][length];

    fgets(str, length ,stdin);
    str[strlen(str) - 1] = '\0';

    puts(str);

    int bi = 0;
    int bj = 0;
    int len = strlen(str);
    for (int i = 0; i <= len; i++) {
        if (isalpha(str[i])) {
            buf[bi][bj] = str[i];
            bj++;
        } else {
            if (bj > 0) {
                buf[bi][bj] = '\0';
                bj = 0;
                bi++;
            }
        }
    }

    for (int i = 0; i < bi; i++) {
        if (strlen(buf[i]) > 0) { 
            puts(buf[i]);
        }
    }

    return 0;
}