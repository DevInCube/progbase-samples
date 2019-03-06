// gcc -g main.c -lprogbase -lm
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#include "sortedkeyvaluelist.h"

int main()
{
    SortedKeyValueList list;
    SortedKeyValueList_init(&list);

    SortedKeyValueList_add(&list, (KeyValue){ "bx", "4" });
    SortedKeyValueList_add(&list, (KeyValue){ "bb", "2" });
    SortedKeyValueList_add(&list, (KeyValue){ "bc", "3" });
    SortedKeyValueList_add(&list, (KeyValue){ "ab", "1" });

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