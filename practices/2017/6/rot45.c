#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    const int n = 7;
    int a[n][n];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            a[i][j] = i * n + j + 1;
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j >= i && i + j < n - 1) {
                int tmp = a[i][j];
                //
                int i3 = j;
                int j3 = n - 1 - i;
                a[i][j] = a[i3][j3];
                int i2 = n - 1 - i;
                int j2 = n - 1 - j;
                a[i3][j3] = a[i2][j2];
                int i1 = n - 1 - j;
                int j1 = i;
                a[i2][j2] = a[i1][j1];
                a[i1][j1] = tmp;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%3i ", a[i][j]);
        }
        puts("");
    }

    return 0;
}

// 1 | 2 | 3 | 4 | 5
// 1 | 2 | 3 | 4

// printf("%i", );