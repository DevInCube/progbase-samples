#ifndef INT_LIST_H
#define INT_LIST_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct IntList IntList;

IntList * IntList_new(void);
void IntList_free(IntList ** selfPtr);

int IntList_get(IntList * self, int index);
void IntList_set(IntList * self, int index, int value);
void IntList_add(IntList * self, int value);
void IntList_insert(IntList * self, int index, int value);
bool IntList_remove(IntList * self, int value);
void IntList_removeAt(IntList * self, int index);
void IntList_clear(IntList * self);
size_t IntList_count(IntList * self);

#endif