#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(void) {
    const int n = 10;
    int a[n];

    for (int i = 0; i < n; i++) {
        a[i] = i + 1;
    }

    for (int i = 0; i < n; i++) {
        printf("%3i, ", a[i]);
    }
    puts("");
    
    puts("1.");
    for (int i = 0; i < n / 2; i++) {
        a[n / 2 + i] = a[i];
    }
    
    for (int i = 0; i < n; i++) {
        printf("%3i, ", a[i]);
    }
    puts("");

    puts("2.");
    for (int i = 0; i < n / 2; i++) {
        a[n - 1 - i] = a[i];
    }
    
    for (int i = 0; i < n; i++) {
        printf("%3i, ", a[i]);
    }
    puts("");

    puts("3.");
    for (int i = 0; i < n; i++) {
        a[i] = i + 1;
    }
    for (int i = 0; i < n / 2; i++) {
        int tmp = a[n - 1 - i];
        a[n - 1 - i] = a[i];
        a[i] = tmp;
    }
    
    for (int i = 0; i < n; i++) {
        printf("%3i, ", a[i]);
    }
    puts("");

    return 0;
}
