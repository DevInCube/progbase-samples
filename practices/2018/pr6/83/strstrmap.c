#include "strstrmap.h"

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
    KeyValue kv; 
    kv.key = key;
    kv.value = value;
    SortedKeyValueList_add(&self->list, kv);
}
bool   StrStrMap_contains     (StrStrMap * self, const char * key)
{ 
    KeyValue kv;
    kv.key = key;
    return SortedKeyValueList_contains(&self->list, kv);
}
const char * StrStrMap_get    (StrStrMap * self, const char * key)
{
    KeyValue kv;
    kv.key = key;
    int index = SortedKeyValueList_indexOf(&self->list, kv);
    if (index < 0) return NULL;
    KeyValue keyValue = SortedKeyValueList_get(&self->list, index);
    return keyValue.value;
}
const char * StrStrMap_set    (StrStrMap * self, const char * key, const char * value)
{
    return NULL; // @todo
}
const char * StrStrMap_remove (StrStrMap * self, const char * key)
{
    KeyValue kv;
    kv.key = key;
    SortedKeyValueList_remove(&self->list, kv);
}
void   StrStrMap_clear        (StrStrMap * self)
{
    // @todo
}