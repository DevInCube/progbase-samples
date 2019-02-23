#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "queue.h"
#include "list.h"

void printStrings(List * pl);
void printTable(List * pl);

char * strOnHeap(const char * str)
{
    char * m = malloc(strlen(str) + 1);
    strcpy(m, str);
    return m;
}

List createTable()
{
    List table;
    List_init(&table);

    //
    List * l = List_alloc();
    List_add(l, strOnHeap("Hello"));
    List_add(l, strOnHeap("Hej"));
    List_add(l, strOnHeap("Hey"));
    //
    List * l1 = List_alloc();
    List_add(l1, strOnHeap("111Hello"));
    List_add(l1, strOnHeap("222Hej"));
    List_add(l1, strOnHeap("333Hey"));
    //
    List_add(&table, l);
    List_add(&table, l1);
    return table;
}

void cleanTable(List * ptable)
{
    for (int i = 0; i < List_size(ptable); i++)
    {
        List * item = List_get(ptable, i);
        for (int j = 0; j < List_size(item); j++)
        {
            char * str = List_get(item, j);
            free(str);
        }
        List_free(item);
    }
    List_deinit(ptable);
}

int main() 
{
    List table = createTable();
    printTable(&table);
    cleanTable(&table);
    return 0;
}

void printTable(List * pl)
{
    for (int i = 0; i < List_size(pl); i++)
    {
        List * item = List_get(pl, i);
        printStrings(item);
    }
}

void printStrings(List * pl)
{
    for (int i = 0; i < List_size(pl); i++)
    {
        char * item = List_get(pl, i);
        printf("\"%s\", ", item);
    }
    printf("\n");
}

int main0()
{
    Queue queue;
    Queue_init(&queue);

    Queue_enqueue(&queue, "first");
    Queue_enqueue(&queue, "2nd");
    Queue_enqueue(&queue, "3rd");

    Queue_print(&queue);

    char * take1 = Queue_dequeue(&queue);
    char * take2 = Queue_dequeue(&queue);

    Queue_print(&queue);

    printf("\n%s\n%s\n", take1, take2);

    Queue_deinit(&queue);
    return 0;
}
