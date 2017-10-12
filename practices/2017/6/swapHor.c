#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    const int width = 3;
    const int height = 3;
    int m[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            m[i][j] = i * width + j;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            int tmp = m[i][j];
            m[i][j] = m[i][width - 1 - j];
            m[i][width - 1 - j] = tmp;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            printf("%3i ", m[i][j]);
        }
        puts("");
    }

    puts("");
    return 0;
}