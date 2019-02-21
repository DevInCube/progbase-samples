#include <stdlib.h>
#include <stdio.h>

#include "dynarray.h"

// DynArray module implementation

void DynArray_init(DynArray *self)
{
    self->length = 0;
    self->capacity = 4;
    self->array = malloc(sizeof(int) * self->capacity);
    if (self->array == NULL)
    {
        fprintf(stderr, "Allocation error");
        abort();
    }
}

void DynArray_deinit(DynArray *self)
{
    free(self->array);
}

static void DynArray_realloc(DynArray *self, int newCapacity)
{
    int *newArray = realloc(self->array, sizeof(int) * newCapacity);
    if (newArray == NULL)
    {
        free(self->array);
        fprintf(stderr, "Reallocation error");
        abort();
    }
    self->array = newArray;
    self->capacity = newCapacity;
    printf("Reallocated");
}

void DynArray_add(DynArray *self, int value)
{
    self->array[self->length] = value;
    //
    self->length += 1;
    //
    if (self->length == self->capacity)
    {
        // realloc
        int newCapacity = self->capacity * 2;
        DynArray_realloc(self, newCapacity);
    }
}

void DynArray_print(const DynArray *self)
{
    for (int i = 0; i < self->length; i++)
    {
        int value = self->array[i];
        printf("%i, ", value);
    }
    printf("\n");
}
