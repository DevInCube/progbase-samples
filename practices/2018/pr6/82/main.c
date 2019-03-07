// gcc *.c
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

#include "sortedkeyvaluelist.h"
#include "strstrmap.h"

static StrStrMap * strings;

int main()
{
    StrStrMap stringsEn;
    StrStrMap_init(&stringsEn);
    StrStrMap_add(&stringsEn, "appname", "My App");
    StrStrMap_add(&stringsEn, "author", "Me");
    StrStrMap_add(&stringsEn, "version", "0.1.1");
    StrStrMap_add(&stringsEn, "type", "console");
    StrStrMap_add(&stringsEn, "file", "a.out");

    StrStrMap ukrainianEn;
    StrStrMap_init(&ukrainianEn);
    StrStrMap_add(&ukrainianEn, "appname", "Moya Programa");
    StrStrMap_add(&ukrainianEn, "author", "Ya");
    StrStrMap_add(&ukrainianEn, "version", "0.1.1");
    StrStrMap_add(&ukrainianEn, "type", "Konsolb");
    StrStrMap_add(&ukrainianEn, "file", "a.out");

    strings = &ukrainianEn;

    printf("=======%s=======\n", StrStrMap_get(strings, "appname"));
    printf("(%s): by %s\n", StrStrMap_get(strings, "version"), StrStrMap_get(strings, "author"));

    // assert(StrStrMap_size(&map) == 5);
    // assert(StrStrMap_contains(&map, "file") == true);
    // assert(StrStrMap_contains(&map, "os") == false);
    // assert(0 == strcmp(StrStrMap_get(&map, "author"), "Me"));
    // StrStrMap_remove(&map, "file");
    // assert(StrStrMap_size(&map) == 4);
    // assert(StrStrMap_contains(&map, "file") == false);

    StrStrMap_deinit(&stringsEn);
    StrStrMap_deinit(&ukrainianEn);
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

    assert(SortedKeyValueList_indexOf(&list, (KeyValue){ "bc", NULL }) == 2);
    assert(SortedKeyValueList_indexOf(&list, (KeyValue){ "xx", NULL }) == -1);

    assert(SortedKeyValueList_contains(&list, (KeyValue){ "bc" }) == true);
    SortedKeyValueList_remove(&list, (KeyValue){ "bc" });
    assert(SortedKeyValueList_contains(&list, (KeyValue){ "bc" }) == false);

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