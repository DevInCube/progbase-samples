// gcc -g main.c -lprogbase -lm
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

#include "sortedkeyvaluelist.h"
#include "strstrmap.h"

int main()
{
    StrStrMap map;
    StrStrMap_init(&map);

    StrStrMap_add(&map, "appname", "Map Sample");
    StrStrMap_add(&map, "version", "v0.1.2");
    StrStrMap_add(&map, "author", "Me");
    StrStrMap_add(&map, "file", "a.out");

    assert(StrStrMap_size(&map) == 4);
    assert(StrStrMap_contains(&map, "version") == true);
    assert(StrStrMap_contains(&map, "os") == false);
    assert(0 == strcmp(StrStrMap_remove(&map, "author"), "Me"));
    assert(StrStrMap_size(&map) == 3);

    assert(0 == strcmp(StrStrMap_get(&map, "version"), "v0.1.2"));
    assert(0 == strcmp(StrStrMap_set(&map, "version", "v0.1.3"), "v0.1.2"));
    assert(0 == strcmp(StrStrMap_get(&map, "version"), "v0.1.3"));

    assert(StrStrMap_size(&map) == 3);

    StrStrMap_deinit(&map);
    return 0;
}

int main0()
{
    SortedKeyValueList list;
    SortedKeyValueList_init(&list);

    SortedKeyValueList_add(&list, (KeyValue){ "bx", "str 4" });
    SortedKeyValueList_add(&list, (KeyValue){ "bb", "str 2" });
    SortedKeyValueList_add(&list, (KeyValue){ "bc", "str 3" });
    SortedKeyValueList_add(&list, (KeyValue){ "ab", "str 1" });

    assert(SortedKeyValueList_contains(&list, (KeyValue){ "xx" }) == false);
    assert(SortedKeyValueList_contains(&list, (KeyValue){ "bc" }) == true);
    assert(SortedKeyValueList_indexOf(&list, (KeyValue){ "bc" }) == 2);
    assert(SortedKeyValueList_size(&list) == 4);
    SortedKeyValueList_remove(&list, (KeyValue){ "bc" });
    assert(SortedKeyValueList_contains(&list, (KeyValue){ "bc" }) == false);
    assert(SortedKeyValueList_indexOf(&list, (KeyValue){ "bc" }) == -1);
    assert(SortedKeyValueList_size(&list) == 3);

    printf("SKVL (%zu): \n", SortedKeyValueList_size(&list));
    for (int i = 0; i < SortedKeyValueList_size(&list); i++)
    {
        KeyValue kv = SortedKeyValueList_get(&list, i);
        printf("{%s:%s}", kv.key, kv.value);
    }
    SortedKeyValueList_deinit(&list);
    puts("\n---");
    return 0;
}