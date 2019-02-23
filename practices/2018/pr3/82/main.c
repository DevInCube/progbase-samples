#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "queue.h"
#include "list.h"

void printStrings(List *pl);
void printStringsTable(List *pl);
List createTable();
void deinitTable(List *p);

typedef enum
{
    CsvReadState_Normal,
    CsvReadState_Escape,
} CsvReadState;

int main()
{
    const char *csvString = "1,2,3\nhi,ho,\n\"ho, ho\nho\"\"ho\",,F";
    // 1      | 2    | 3    |
    // hi     | ho   |      |
    // ho, ho |      | F    |
    char buf[100];
    int bufX = 0;
    CsvReadState state = CsvReadState_Normal;
    char *p = (char *)csvString;
    while (1)
    {
        if (state == CsvReadState_Normal)
        {
            if (*p == '"')
            {
                state = CsvReadState_Escape;
            }
            else
            {
                if (*p == '\n' || *p == ',' || *p == '\0')
                {
                    buf[bufX] = '\0';
                    printf("[%s]", buf);
                    if (*p == '\n')
                    {
                        printf("\n");
                    }
                    //
                    bufX = 0;
                }
                else
                {
                    buf[bufX] = *p;
                    bufX += 1;
                }
            }
        }
        else // escaped
        {
            if (*p == '"')
            {
                if (*(p + 1) == '"')
                {
                    buf[bufX] = '"';
                    bufX += 1;

                    p += 1;
                }
                else
                {
                    buf[bufX] = '\0';
                    printf("[%s]", buf);
                    //
                    bufX = 0;
                    //
                    if (*(p + 1) == ',')
                    {
                        p += 1;
                        state = CsvReadState_Normal;
                    }
                    else 
                    {
                        fprintf(stderr, "CSV format error: invalid char '%c' after escape\n", *(p + 1));
                        abort();
                    }
                }
            }
            else
            {
                buf[bufX] = *p;
                bufX += 1;
            }
        }

        if (*p == '\0')
        {
            break;
        }
        p += 1;
    }

    // List table = createTable();
    // printStringsTable(&table);
    // deinitTable(&table);
    return 0;
}

void deinitTable(List *p)
{
    for (int i = 0; i < List_size(p); i++)
    {
        List *row = List_get(p, i);
        for (int j = 0; j < List_size(row); j++)
        {
            char *str = List_get(row, j);
            free(str);
        }
        List_free(row);
    }
    List_deinit(p);
}

char *createOnHeap(const char *str)
{
    char *meme = malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(meme, str);
    return meme;
}

List createTable()
{
    List table;
    List_init(&table);

    List *pl = List_alloc();

    List_add(pl, createOnHeap("Hej!"));
    List_add(pl, createOnHeap("Hey!"));
    List_add(pl, createOnHeap("Hi!"));

    List_add(&table, pl);

    List *pl2 = List_alloc();

    List_add(pl2, createOnHeap("Hello!"));
    List_add(pl2, createOnHeap("Hallo!"));

    List_add(&table, pl2);
    return table;
}

void printStringsTable(List *pl)
{
    for (int i = 0; i < List_size(pl); i++)
    {
        List *row = List_get(pl, i);
        printStrings(row);
    }
}

void printStrings(List *pl)
{
    for (int i = 0; i < List_size(pl); i++)
    {
        char *item = List_get(pl, i);
        printf("\"%s\", ", item);
    }
    printf("\n");
}

int main0(int argc, char const *argv[])
{
    Queue q1;
    Queue_init(&q1);

    assert(Queue_size(&q1) == 0);

    Queue_enqueue(&q1, 13);
    assert(Queue_size(&q1) == 1);

    Queue_enqueue(&q1, -42);
    assert(Queue_size(&q1) == 2);
    assert(Queue_dequeue(&q1) == 13);
    assert(Queue_size(&q1) == 1);
    assert(Queue_dequeue(&q1) == -42);

    Queue_deinit(&q1);
    return 0;
}
