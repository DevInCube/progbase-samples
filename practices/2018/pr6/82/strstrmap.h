#pragma once

#include "sortedkeyvaluelist.h"

typedef struct __StrStrMap StrStrMap;
struct __StrStrMap
{
    SortedKeyValueList list;
};
// comparer function: strcmp
/* paste _init(), _deinit(), _alloc(), _free() prototypes here */

void StrStrMap_init(StrStrMap * self);
void StrStrMap_deinit(StrStrMap * self);

size_t StrStrMap_size         (StrStrMap * self);

void   StrStrMap_add          (StrStrMap * self, const char * key, const char * value);
bool   StrStrMap_contains     (StrStrMap * self, const char * key);
const char * StrStrMap_get    (StrStrMap * self, const char * key);
const char * StrStrMap_set    (StrStrMap * self, const char * key, const char * value);
const char * StrStrMap_remove (StrStrMap * self, const char * key);
void   StrStrMap_clear        (StrStrMap * self);
