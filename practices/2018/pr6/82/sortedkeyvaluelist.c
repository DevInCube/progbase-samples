#include <string.h>
#include <stdlib.h>

#include "sortedkeyvaluelist.h"

void SortedKeyValueList_init(SortedKeyValueList * self)
{
    self->capacity = 16;
    self->items = malloc(sizeof(KeyValue) * self->capacity);
    self->size = 0;
}
void SortedKeyValueList_deinit(SortedKeyValueList * self)
{
    free(self->items);
}

size_t  SortedKeyValueList_size     (SortedKeyValueList * self)
{
    return self->size;
}
KeyValue     SortedKeyValueList_get      (SortedKeyValueList * self, int index)
{
    return self->items[index];
}

void    SortedKeyValueList_set      (SortedKeyValueList * self, int index, KeyValue value)
{
    self->items[index] = value;  
}

void    SortedKeyValueList_removeAt (SortedKeyValueList * self, int index)
{
    // @todo check index
    for (int i = index; i < self->size - 1; i++)
    {
        self->items[i] = self->items[i + 1];
    }
    self->size -= 1;
}

int KeyValue_compare(const KeyValue * a, const KeyValue * b)
{
    return strcmp(a->key, b->key);
}

void    SortedKeyValueList_add      (SortedKeyValueList * self, KeyValue kv)
{
    for (int i = self->size; i >= 0; i--) 
    {
        if (i == 0) 
        {
            // stop
            self->items[i] = kv;
        }
        else 
        {
            int cmp = KeyValue_compare(&kv, &self->items[i - 1]);
            if (cmp >= 0)
            {
                // stop
                self->items[i] = kv;
                break;
            }
            else 
            {
                self->items[i] = self->items[i - 1];
            }
        }
    } 
    self->size += 1;
    // @todo realloc
}
void    SortedKeyValueList_remove   (SortedKeyValueList * self, KeyValue kv)
{
    int index = SortedKeyValueList_indexOf(self, kv);
    if (index == -1) return;
    for (int i = index; i < self->size - 1; i++)
    {
        self->items[i] = self->items[i + 1]; 
    }
    self->size -= 1; 
}

int SortedKeyValueList_indexOf  (SortedKeyValueList * self, KeyValue kv)
{
    //self->items
    KeyValue * item = bsearch(&kv, self->items, self->size, sizeof(KeyValue), (__compar_fn_t)KeyValue_compare);
    if (item == NULL) return -1;
    return item - self->items; 
}
bool    SortedKeyValueList_contains (SortedKeyValueList * self, KeyValue kv)
{
    return SortedKeyValueList_indexOf(self, kv) >= 0;
}

void    SortedKeyValueList_clear    (SortedKeyValueList * self)
{
    self->size = 0;
}
