#pragma once

// DynArray module interface
typedef struct __DynArray DynArray;
struct __DynArray
{
    int *array;
    int capacity;
    int length;
};

void DynArray_init(DynArray *self);
void DynArray_deinit(DynArray *self);
void DynArray_add(DynArray *self, int value);
void DynArray_print(const DynArray *self);
//