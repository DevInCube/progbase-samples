#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>

void printArr(int a[], int length);
void printMin(int a[], int length);
int min(int a[], int length);
void revertArrSigns(int a[], int length);
void fillArrRandom(int a[], int length, int min, int max);
int arrEquals(int a[], int aLength, int b[], int bLength);
void sortSigns(int a[], int aLength, int b[]);

int main(void) {
    int a[] = {4, -5, 5, -4};
    int b[4];
    sortSigns(a, 4, b);
    assert(arrEquals(b, 4, (int[]){-5, -4, 5, 4}, 4) == 1);
    return 0;
}

void sortSigns(int a[], int aLength, int b[]) {
    int posPos = aLength - 1;
    int negPos = 0;
    for (int i = 0; i < aLength; i++) {
        if (a[i] < 0) {
            b[negPos] = a[i];
            negPos++;
        } else {
            b[posPos] = a[i];
            posPos--;
        }
    }
}

int arrEquals(int a[], int aLength, int b[], int bLength) {
    if (aLength != bLength) return 0;
    for (int i = 0; i < aLength; i++) {
        if (a[i] != b[i]) return 0;
    }
    return 1;
}

void fillArrRandom(int a[], int length, int min, int max) {
    for (int i = 0; i < length; i++) {
        a[i] = (rand() % (max - min + 1)) + min;
    }
}

void revertArrSigns(int a[], int length) {
    for (int i = 0; i < length; i++) {
        a[i] = -a[i];
    }
}

void printMin(int a[], int length) {
    int minValue = min(a, length);
    printf("Min is %i\n", minValue);
}

int min(int a[], int length) {
    int m = a[0];
    for (int i = 1; i < length; i++) {
        if (a[i] < m) {
            m = a[i];
        }
    }
    return m;
}

void printArr(int a[], int length) {
    for (int i = 0; i < length; i++) {
        printf("%3i, ", a[i]);
    }
    puts("");
}