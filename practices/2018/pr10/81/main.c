#include <stdio.h>
#include <stdlib.h>
#include <string.h>

union Number
{
    int integer;
    double dbl;
    char str[20];
};

int main(int argc, char const *argv[])
{
    union Number num;
    num.integer = 45;
    printf("int: %i\n", num.integer);
    num.dbl = 34.5;
    printf("dbl: %lf\n", num.dbl);
    printf("size: %zu\n", sizeof(num));
    strcpy(num.str, "1000");
    printf("str: %s\n", num.str);
    return 0;
}
