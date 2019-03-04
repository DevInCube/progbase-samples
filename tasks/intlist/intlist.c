#include "intlist.h"

void IntList_init(IntList * self)
{
    self->capacity = 16;
    self->size = 0;
    self->items = malloc(sizeof(int) * self->capacity);
    if (self->items == NULL)
    {
        // @todo
    }
}
void IntList_deinit(IntList * self)
{
    free(self->items);
}

IntList *  IntList_alloc (void) 
{
    IntList * self = malloc(sizeof(IntList));
    IntList_init(self);
    return self;
}
void    IntList_free     (IntList * self)
{
    IntList_deinit(self);
    free(self);
}

size_t  IntList_size     (IntList * self) { return self->size; }
int     IntList_get      (IntList * self, int index) { return self->items[index]; }
void    IntList_set      (IntList * self, int index, int value) { self->items[index] = value; }
void    IntList_insert   (IntList * self, int index, int value) 
{
    // @todo implement with shift
}
void    IntList_removeAt (IntList * self, int index)
{
    // @todo implement with shift 
    for (int i = index; i < self->size - 1; i++)
    {
        self->items[i] = self->items[i + 1];
    }
    self->size -= 1;
}

void    IntList_add      (IntList * self, int value) 
{
    if (self->size == self->capacity) 
    {
        // @todo realloc self->items
    }
    self->items[self->size++] = value; 
}
void    IntList_remove   (IntList * self, int value) 
{
    // @todo implement
}
int     IntList_indexOf  (IntList * self, int value)
{
    // @todo implement
    return -1;
}
bool    IntList_contains (IntList * self, int value) 
{
    // @todo implement search
    return false;
}
bool    IntList_isEmpty  (IntList * self) { return self->size == 0; }
void    IntList_clear    (IntList * self) { self->size = 0; }