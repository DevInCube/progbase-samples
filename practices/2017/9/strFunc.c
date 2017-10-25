#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

void myPuts(char str[]);
int myStrlen(char str[]);
int stringEquals(char a[], char b[]); // strcmp

int main(void) {
    assert(stringEquals("", "") == 1);
    assert(stringEquals("", "Hello") == 0);
    assert(stringEquals("Hello", "Hello") == 1);
    assert(stringEquals("Hello", "hello") == 0);
    assert(stringEquals("Hello", "Hello!") == 0);
    return 0;
}

int stringEquals(char a[], char b[]) {
    return strcmp(a, b) == 0;
}

void myPuts(char str[]) {
    int i = 0;
    while(str[i] != '\0') {
        putchar(str[i]);
        i++;
    }
    putchar('\n');
}

int myStrlen(char str[]) {
    int i = 0;
    while(str[i] != '\0') {
        i++;
    }
    return i;
}