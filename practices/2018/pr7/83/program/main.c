// gcc *.c
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

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
