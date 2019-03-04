// gcc -g *.c
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#include "dynarray.h"

void printArray(DynamicIntArray * pArr)
{
    for (int i = 0; i < DynamicIntArray_size(pArr); i++)
    {
        int val = DynamicIntArray_get(pArr, i);
        printf("%i, ", val);
    }
    printf("\n");
}

int main()
{
    puts("STACK:");
    //
    DynamicIntArray arr;
    DynamicIntArray_init(&arr, 10);

    for (int i = 0; i < DynamicIntArray_size(&arr); i++)
    {
        DynamicIntArray_set(&arr, i, 42);
    }
    printArray(&arr);
    DynamicIntArray_resize(&arr, 20);
    for (int i = 10; i < DynamicIntArray_size(&arr); i++)
    {
        DynamicIntArray_set(&arr, i, 13);
    }
    printArray(&arr);
    DynamicIntArray_resize(&arr, 15);
    printArray(&arr);

    DynamicIntArray_deinit(&arr);
    //
    puts("HEAP:");
    //
    DynamicIntArray * p = DynamicIntArray_alloc(10);
    
    for (int i = 0; i < DynamicIntArray_size(p); i++)
    {
        DynamicIntArray_set(p, i, 42);
    }
    printArray(p);
    DynamicIntArray_resize(p, 20);
    for (int i = 10; i < DynamicIntArray_size(p); i++)
    {
        DynamicIntArray_set(p, i, 13);
    }
    printArray(p);
    DynamicIntArray_resize(p, 15);
    printArray(p);

    DynamicIntArray_free(p);
    //
    puts("\n---");
    return 0;
}