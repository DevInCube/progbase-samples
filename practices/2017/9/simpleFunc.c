#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

int min2(int a, int b);
int min3(int a, int b, int c);

double f(double x, double y);
int doubleEquals(double a, double b);

int main(void) {
    assert(min2(4, 6) == 4);
    assert(min2(4, -1) == -1);
    assert(min2(0, 0) == 0);
    //
    assert(min3(4, 6, 2) == 2);
    assert(min3(4, -1, 45) == -1);
    assert(min3(0, 0, 0) == 0);
    assert(min3(-3, -4, -5) == -5);
    //
    assert(doubleEquals(f(1, 2), 5.0));
    assert(isnan(f(0, 2)));
    assert(doubleEquals(f(4.5, -3.4), 12.031404));
    return 0;
}

int doubleEquals(double a, double b) {
    return fabs(a - b) < 0.00001;
}

double f(double x, double y) {
    if (x <= 0) {
        return NAN;
    }
    return sqrt(1/x) + pow(y,2);
}

int min3(int a, int b, int c) {
    return min2(min2(a, b), c);
}

int min2(int a, int b) {
    return a < b ? a : b;
}