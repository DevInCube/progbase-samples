#include "sortedkeyvaluelist.h"
#include <string.h>

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
void    SortedKeyValueList_removeAt (SortedKeyValueList * self, int index)
{
    // @todo check index
    for (int i = index; i < self->size - 1; i++)
    {
        self->items[i] = self->items[i + 1];
    }
    self->size -= 1;
}

void    SortedKeyValueList_add      (SortedKeyValueList * self, KeyValue kv)
{
    const char * newKey = kv.key;
    for (int i = self->size; i >= 0; i--) 
    {
        if (i == 0) 
        {
            // stop
            self->items[i] = kv;
        }
        else 
        {
            const char * prevKey = self->items[i - 1].key;
            int cmp = strcmp(newKey, prevKey);
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
    const char * newKey = kv.key;
}
int     SortedKeyValueList_indexOf  (SortedKeyValueList * self, KeyValue kv)
{
    const char * newKey = kv.key;
    return -1;
}
bool    SortedKeyValueList_contains (SortedKeyValueList * self, KeyValue kv)
{
    const char * newKey = kv.key;
    return false;
}
