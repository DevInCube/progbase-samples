#pragma once

#include <stdlib.h>

// DynArray interface
struct __DynArray
{ 
    int cap;
    size_t length;
    char *arr;
};

typedef struct __DynArray DynArray;

void DynArray_init(DynArray *darray); 
void DynArray_deinit(DynArray *darray);
void DynArray_add(DynArray *darray, char newValue);
void DynArray_print(const DynArray *darray);
//