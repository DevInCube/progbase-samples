#include "list.h"

void    List_init     (List * self)
{
    self->capacity = 4;
    self->size = 0;
    self->items = malloc(sizeof(void *) * self->capacity);
    // @todo NULL check
}
void    List_deinit   (List * self)
{
    free(self->items);
}

List *  List_alloc    (void)
{
    List * self = malloc(sizeof(List));
    List_init(self);
    return self;
}
void    List_free     (List * self)
{
    List_deinit(self);
    free(self);
}

T List_get      (List * self, int index)
{
    return self->items[index]; 
}
void    List_set      (List * self, int index, T value)
{

}
size_t  List_size     (List * self)
{
    return self->size;
}
void    List_insert   (List * self, int index, T value)
{

}
void    List_removeAt (List * self, int index)
{

}

void    List_add      (List * self, T value)
{
    self->items[self->size] = value;
    self->size += 1;
    // @todo resize
}
void    List_remove   (List * self, T value)
{
    
}
int     List_indexOf  (List * self, T value)
{
    return -1;
} 
bool    List_contains (List * self, T value)
{
    return false;
}
bool    List_isEmpty  (List * self)
{
    return false;
}
void    List_clear    (List * self)
{

}