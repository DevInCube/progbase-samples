#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(void)
{
    system("clear");
    const int length = 10;
    const int amp = 10;
    double a[length];

    for (int i = 0; i < length; i++)
    {
        a[i] = amp * sin(i);
    }

    puts("y: ");
    for (int i = 0; i < length; i++)
    {
        printf("%.2f ", a[i]);
    }

    double b[length - 1];

    for (int i = 0; i < length - 1; i++)
    {
        b[i] = a[i + 1] - a[i];
    }

    puts("");
    puts("dy: ");
    for (int i = 0; i < length; i++)
    {
        printf("%.2f ", b[i]);
    }

    puts("");

    return 0;
}
