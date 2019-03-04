#pragma once
#include <stdlib.h>
#include <stdbool.h>

typedef struct __IntList IntList;

struct __IntList 
{
    int * items;   // a pointer to allocated memory of an array
    int capacity;  // a number of items in allocated array memory
    int size;      // number of the first array items that hold the values of the list
};

void IntList_init(IntList * self);    // instance initialization (items malloc)
void IntList_deinit(IntList * self);  // instance deinitialization (items free)

IntList *  IntList_alloc (void);
void    IntList_free     (IntList * self);

size_t  IntList_size     (IntList * self);
int     IntList_get      (IntList * self, int index);
void    IntList_set      (IntList * self, int index, int value);
void    IntList_insert   (IntList * self, int index, int value);
void    IntList_removeAt (IntList * self, int index);

void    IntList_add      (IntList * self, int value);
void    IntList_remove   (IntList * self, int value);
int     IntList_indexOf  (IntList * self, int value);
bool    IntList_contains (IntList * self, int value);
bool    IntList_isEmpty  (IntList * self);
void    IntList_clear    (IntList * self);