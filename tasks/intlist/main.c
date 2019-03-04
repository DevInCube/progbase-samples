// gcc -g *.c
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#include "intlist.h"

void IntList_fillRandom(IntList * list, int n, int min, int max);
void IntList_print(IntList * list);
void IntList_removeAllNegative(IntList * list);

int main()
{
    srand(time(NULL)); 
    IntList numbers;
    IntList_init(&numbers);

    IntList_fillRandom(&numbers, 10, -100, 100);
    IntList_print(&numbers);
    IntList_removeAllNegative(&numbers);
    IntList_print(&numbers);

    IntList_deinit(&numbers);
    puts("\n---");
    return 0;
}

void IntList_fillRandom(IntList * list, int n, int min, int max)
{
    for (int i = 0; i < n; i++)
    {
        int num = rand() % (max - (min) + 1) + (min);
        IntList_add(list, num);
    }
}

void IntList_print(IntList * list)
{
    for (int i = 0; i < IntList_size(list); i++)
    {
        int value = IntList_get(list, i);
        printf("%i, ", value);
    }
    printf("\n");
    fflush(stdout);
}

void IntList_removeAllNegative(IntList * list)
{
    for (int i = 0; i < IntList_size(list); i++)
    {
        int value = IntList_get(list, i);
        if (value < 0) 
        {
            printf("Removing %i at %i\n", value, i);
            IntList_removeAt(list, i);
            i -= 1;
        }
    }
}