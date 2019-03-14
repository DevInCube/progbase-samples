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

static StrStrMap * strings;

int main()
{
    StrStrMap stringsEn;
    StrStrMap_init(&stringsEn);
    StrStrMap_add(&stringsEn, "AppName", "My console test app");
    StrStrMap_add(&stringsEn, "Version", "Version");
    StrStrMap_add(&stringsEn, "VersionNum", "0.1.3");
    StrStrMap_add(&stringsEn, "AuthorName", "me");

    StrStrMap stringsUa;
    StrStrMap_init(&stringsUa);
    StrStrMap_add(&stringsUa, "AppName", "Moya konsolbna programa");
    StrStrMap_add(&stringsUa, "Version", "Versija");
    StrStrMap_add(&stringsUa, "VersionNum", "0.1.3");
    StrStrMap_add(&stringsUa, "AuthorName", "ja");

    strings = &stringsUa;

    printf("====%s====\n", StrStrMap_get(strings, "AppName"));
    printf("%s %s by %s\n", 
        StrStrMap_get(strings, "Version"), 
        StrStrMap_get(strings, "VersionNum"), 
        StrStrMap_get(strings, "AuthorName"));

    StrStrMap_deinit(&stringsEn);
    StrStrMap_deinit(&stringsUa);
    return 0;
}

int main1()
{
    StrStrMap map;
    StrStrMap_init(&map);

    StrStrMap_add(&map, "appname", "My console test app");
    StrStrMap_add(&map, "version", "0.1.3");
    StrStrMap_add(&map, "author", "me");

    //
    assert(StrStrMap_contains(&map, "version") == true);
    assert(StrStrMap_contains(&map, "os") == false);
    assert(strcmp(StrStrMap_get(&map, "version"), "0.1.3") == 0);
    assert(strcmp(StrStrMap_remove(&map, "version"), "0.1.3") == 0);
    assert(StrStrMap_contains(&map, "version") == false);
    //
    StrStrMap_deinit(&map);
    return 0;
}

int main0()
{
    SortedKeyValueList list;
    SortedKeyValueList_init(&list);

    SortedKeyValueList_add(&list, (KeyValue){"ax", "ax Value 1"});
    SortedKeyValueList_add(&list, (KeyValue){"ad", "ad Value 2"});
    SortedKeyValueList_add(&list, (KeyValue){"dt", "dt Value 3"});
    SortedKeyValueList_add(&list, (KeyValue){"bc", "bc Value 4"});

    for (int i = 0; i < SortedKeyValueList_size(&list); i++)
    {
        KeyValue kv = SortedKeyValueList_get(&list, i);
        printf("{%s:%s},", kv.key, kv.value);
    }

    assert(SortedKeyValueList_indexOf(&list, (KeyValue){"dt"}) == 3);
    assert(SortedKeyValueList_contains(&list, (KeyValue){"dt"}) == true);
    assert(SortedKeyValueList_contains(&list, (KeyValue){"dd"}) == false);
    SortedKeyValueList_remove(&list, (KeyValue){"dt"});
    assert(SortedKeyValueList_contains(&list, (KeyValue){"dt"}) == false);

    puts("\n---");
    SortedKeyValueList_deinit(&list);
    return 0;
}