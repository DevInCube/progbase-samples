#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int a[4];

    for (int i = 0; i < 4; i++) {
        a[i] = i + 1;
    }
    puts("a: ");
    for (int i = 0; i < 4; i++) {
        printf("%3i, ", a[i]);
    }
    // @todo shift left by 1
    int tmp = a[0];
    for (int i = 0; i < 3; i++) {
        a[i] = a[i + 1];
    }
    a[3] = tmp;
    puts("\nshifted a: ");
    for (int i = 0; i < 4; i++) {
        printf("%3i, ", a[i]);
    }
    puts("");
    return 0;
}