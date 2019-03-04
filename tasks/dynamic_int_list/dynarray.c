#include "dynarray.h"

void    DynamicIntArray_init   (DynamicIntArray * self, size_t size)
{
    self->items = malloc(sizeof(int) * size);
    self->capacity = size;
}
void    DynamicIntArray_deinit (DynamicIntArray * self)
{
    free(self->items);
}
DynamicIntArray * DynamicIntArray_alloc  (size_t size)
{
    DynamicIntArray * self = malloc(sizeof(DynamicIntArray));
    DynamicIntArray_init(self, size);
    return self;
}
void    DynamicIntArray_free   (DynamicIntArray * self)
{
    DynamicIntArray_deinit(self);
    free(self);
}

size_t  DynamicIntArray_size   (DynamicIntArray * self)
{
    return self->capacity;
}
bool    DynamicIntArray_resize (DynamicIntArray * self, size_t newSize)
{
    int * newMem = realloc(self->items, sizeof(int) * newSize);
    if (newMem == NULL) {
        return false;
    }
    self->items = newMem;
    self->capacity = newSize;
    return true;
}

int     DynamicIntArray_get    (DynamicIntArray * self, int index)
{
    return self->items[index];
}
void    DynamicIntArray_set    (DynamicIntArray * self, int index, int value)
{
    self->items[index] = value;
}