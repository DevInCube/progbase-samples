#include <stdlib.h>
#include <stdio.h>

#include "dynarray.h"

// DynArray impl
 
void DynArray_deinit(DynArray *darray)
{
    free(darray->arr);

}

void DynArray_add(DynArray *darray, char newValue)
{
    darray->arr[darray->length] = newValue;
    darray->length += 1;
    // realloc mem
    if (darray->length == darray->cap)
    {
        int newcap = darray->cap * 2;
        char *newarr = realloc(darray->arr, sizeof(char) * newcap);
        if (newarr == NULL)
        {
            free(darray->arr);
            fprintf(stderr, "Reallocating memory error\n");
            abort();
        }
        printf("Reallocated from %i to %i\n", darray->cap, newcap);
        darray->arr = newarr;
        darray->cap = newcap;
    }
}

void DynArray_print(const DynArray *darray)
{
    for (int i = 0; i < darray->length; i++)
    {
        printf("%c,", darray->arr[i]);
    }
    printf("\n");
}

void DynArray_init(DynArray *darray)
{ 
    darray->cap = 4;
    darray->arr = malloc(sizeof(char) * darray->cap);
    if (darray == NULL) 
    {
        fprintf(stderr, "Allocating memory error\n");
        abort();
    }
    darray->length = 0;
}

//