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