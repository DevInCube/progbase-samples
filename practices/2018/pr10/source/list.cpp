#include "list.h"

//
static void List_InvalidIndexError()
{
    assert(0 && "Invalid index");
    fprintf(stderr, "Invalid index");
}
//
static void List_realloc(List *self, size_t newCapacity)
{
    void *newArray = realloc(self->items, sizeof(self->items[0]) * newCapacity);
    if (newArray == NULL)
    {
        fprintf(stderr, "Reallocation error\n");
        abort();
    }
    self->items = static_cast<T*>(newArray);
    self->capacity = newCapacity;
    printf("Reallocated\n");
}

List *List_alloc(void)
{
    List *list = static_cast<List*>(malloc(sizeof(List)));
    List_init(list);
    return list;
}
//
void List_free(List *self)
{
    List_deinit(self);
    free(self);
}
//
void List_init(List *self)
{
    self->capacity = 16;
    self->size = 0;
    self->items = static_cast<T*>(malloc(sizeof(self->items[0]) * self->capacity));
    if (self->items == NULL)
    {
        fprintf(stderr, "Allocation error\n");
        abort();
    }
}
//
void List_deinit(List *self)
{
    free(self->items);
}
size_t List_size(List *self)
{
    return self->size;
}
//
void *List_get(List *self, int index)
{
    if (index < 0 || index > List_size(self))
    {
        List_InvalidIndexError();
        return NULL;
    }
    return self->items[index];
}
//
void List_set(List *self, int index, void *value)
{
    self->items[index] = value;
}
//
void List_insert(List *self, int index, void *value)
{
    if (index < 0 || index > List_size(self))
    {
        List_InvalidIndexError();
        return;
    }

    if (self->size == self->capacity)
    {
        int newCapacity = self->capacity * 2;
        List_realloc(self, newCapacity);
    }

    for (int i = List_size(self) - 1; i >= index; i--)
    {
        self->items[i + 1] = self->items[i];
    }
    self->items[index] = value;
    self->size += 1;
}
//
void List_removeAt(List *self, int index)
{
    if (index < 0 || index > List_size(self))
    {
        List_InvalidIndexError();
        return;
    }

    for (int i = index; i < List_size(self); i++)
    {
        self->items[i] = self->items[i + 1];
    }
    self->size -= 1;
}
//
void List_add(List *self, void *value)
{
    if (List_size(self) == self->capacity)
    {
        int newCapacity = self->capacity * 2;
        List_realloc(self, newCapacity);
    }
    self->items[self->size] = value;
    self->size += 1;
}
//
void List_remove(List *self, void *value)
{
    List_removeAt(self, List_indexOf(self, value));
}
//
int List_indexOf(List *self, void *value)
{
    for (int i = 0; i < List_size(self); i++)
    {
        if (self->items[i] == value)
        {
            return i;
        }
    }
    return -1;
}
//
bool List_contains(List *self, void *value)
{
    int index = List_indexOf(self, value);
    if (index != -1)
    {
        return List_get(self, index) != NULL;
    }
    return false;
}
//
bool List_isEmpty(List *self)
{
    return List_size(self) == 0;
}
//
void List_clear(List *self)
{
    self->size = 0;
}