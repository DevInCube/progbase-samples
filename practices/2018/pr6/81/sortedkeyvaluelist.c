#include "sortedkeyvaluelist.h"
#include <string.h>
#include <stdio.h>

void SortedKeyValueList_init(SortedKeyValueList * self)
{
    self->capacity = 16;
    self->size = 0;
    self->items = malloc(sizeof(KeyValue) * self->capacity); 
}
void SortedKeyValueList_deinit(SortedKeyValueList * self)
{
    free(self->items);
}
SortedKeyValueList * SortedKeyValueList_alloc()
{
    SortedKeyValueList * self = malloc(sizeof(SortedKeyValueList));
    SortedKeyValueList_init(self);
    return self;
}
void SortedKeyValueList_free(SortedKeyValueList * self)
{
    SortedKeyValueList_deinit(self);
    free(self); 
}

int KeyValue_compare(KeyValue * a, KeyValue * b)
{
    int cmp = strcmp(a->key, b->key);
    return cmp;
}

//

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
    KeyValue * old = &self->items[index];
    if (KeyValue_compare(old, &value) == 0)
    {
        self->items[index] = value;
    }
    else 
    {
        fprintf(stderr, "Sorted list replace violation");
        abort();
    } 
}

void    SortedKeyValueList_removeAt (SortedKeyValueList * self, int index)
{
    for (int i = index; i < self->size - 1; i++)
    {
        self->items[i] = self->items[i + 1];
    }
    self->size -= 1;
}

void    SortedKeyValueList_add      (SortedKeyValueList * self, KeyValue value)
{
    for (int i = self->size; i >= 0; i--)
    {
        if (i == 0)
        {
            self->items[0] = value;
            break;
        }
        else 
        {
            KeyValue * prev = &(self->items[i - 1]);
            KeyValue * curr = &value;
            if (KeyValue_compare(prev, curr) <= 0)
            {
                self->items[i] = value;
                break;
            }
            else
            {
                self->items[i] = self->items[i - 1];
            }
        }
    }
    self->size += 1;
}

void    SortedKeyValueList_remove   (SortedKeyValueList * self, KeyValue value)
{
    int rIndex = SortedKeyValueList_indexOf(self, value);
    if (rIndex == -1) return;
    SortedKeyValueList_removeAt(self, rIndex);
}

int     SortedKeyValueList_indexOf  (SortedKeyValueList * self, KeyValue value)
{
    KeyValue * item = bsearch(
        &value, 
        self->items,
        self->size, 
        sizeof(KeyValue), 
        (__compar_fn_t)KeyValue_compare);
    if (item == NULL)
    {
        return -1;
    }
    return item - self->items;
}
bool    SortedKeyValueList_contains (SortedKeyValueList * self, KeyValue value)
{
    return SortedKeyValueList_indexOf(self, value) != -1;
}

bool    SortedKeyValueList_isEmpty  (SortedKeyValueList * self)
{
    return self->size == 0;
}
void    SortedKeyValueList_clear    (SortedKeyValueList * self)
{
    self->size = 0;
}