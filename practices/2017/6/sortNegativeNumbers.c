#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(void)
{
    srand(time(0));
    int a[10];
    for (int i = 0; i < 10; i++)
    {
        a[i] = (rand() % 201) - 100;
        printf("a[%i] = %i\r\n", i, a[i]);
    }
    puts("-------------------");
    
    int b[10];
     
    // clear array
    for (int i = 0; i < 10; i++)
    {
        b[i] = 0;
    }

    int negativePosition = 0;
    for (int i = 0; i < 10; i++) {
        if (a[i] < 0) {
            b[negativePosition] = a[i];
            negativePosition++;
        }
    }

    // print array
    for (int i = 0; i < 10; i++)
    {
        printf("b[%i] = %i\r\n", i, b[i]);
    }

    return 0;
}
