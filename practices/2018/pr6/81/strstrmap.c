#include "strstrmap.h"
#include <stdio.h>

void StrStrMap_init(StrStrMap * self)
{
    SortedKeyValueList_init(&self->list);
}
void StrStrMap_deinit(StrStrMap * self)
{
    SortedKeyValueList_deinit(&self->list);
}

size_t StrStrMap_size         (StrStrMap * self)
{
    return SortedKeyValueList_size(&self->list);
}

void   StrStrMap_add          (StrStrMap * self, const char * key, const char * value)
{ 
    SortedKeyValueList_add(&self->list, (KeyValue) { key, value });
}
bool   StrStrMap_contains     (StrStrMap * self, const char * key)
{
    return SortedKeyValueList_contains(&self->list, (KeyValue) { key });
}
const char * StrStrMap_get    (StrStrMap * self, const char * key)
{
    int index = SortedKeyValueList_indexOf(&self->list, (KeyValue) { key });
    if (index == -1)
    {
        fprintf(stderr, "Key `%s` not found\n", key);
        abort();
    }
    KeyValue kv = SortedKeyValueList_get(&self->list, index);
    return kv.value;  
}
const char * StrStrMap_set    (StrStrMap * self, const char * key, const char * value)
{
    int index = SortedKeyValueList_indexOf(&self->list, (KeyValue) { key });
    if (index == -1)
    {
        fprintf(stderr, "Key `%s` not found\n", key);
        abort();
    }
    KeyValue oldItem = SortedKeyValueList_get(&self->list, index);
    SortedKeyValueList_set(&self->list, index, (KeyValue) { key, value });
    return oldItem.value;
}
const char * StrStrMap_remove (StrStrMap * self, const char * key)
{
    int index = SortedKeyValueList_indexOf(&self->list, (KeyValue) { key });
    if (index == -1)
    {
        fprintf(stderr, "Key `%s` not found\n", key);
        abort();
    }
    KeyValue oldItem = SortedKeyValueList_get(&self->list, index);
    SortedKeyValueList_remove(&self->list, (KeyValue) { key });
    return oldItem.value;
}
void   StrStrMap_clear        (StrStrMap * self)
{
    SortedKeyValueList_clear(&self->list);
}