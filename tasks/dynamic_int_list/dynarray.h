#pragma once
#include <stdlib.h>
#include <stdbool.h>

typedef struct __DynamicIntArray DynamicIntArray;
struct __DynamicIntArray
{
    int  * items;
    size_t capacity;
};

void    DynamicIntArray_init   (DynamicIntArray * self, size_t size);
void    DynamicIntArray_deinit (DynamicIntArray * self);
DynamicIntArray * DynamicIntArray_alloc  (size_t size);
void    DynamicIntArray_free   (DynamicIntArray * self);

size_t  DynamicIntArray_size   (DynamicIntArray * self);
bool    DynamicIntArray_resize (DynamicIntArray * self, size_t newSize);

int     DynamicIntArray_get    (DynamicIntArray * self, int index);
void    DynamicIntArray_set    (DynamicIntArray * self, int index, int value);
