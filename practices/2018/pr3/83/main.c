#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>

#include "dynarray.h"
#include "stack.h"
#include "list.h"

int typeEquals(char a, char b);
int isBalanced(const char *str);

char *strOnHeap(const char *strLit1)
{
    char *str1 = malloc(sizeof(char) * strlen(strLit1) + 1);
    strcpy(str1, strLit1);
    return str1;
}

List createList(int lineLen, char *line[lineLen])
{
    List l;
    List_init(&l);

    for (int i = 0; i < lineLen; i++)
    {
        char *item = line[i];
        List_add(&l, strOnHeap(item));
    }

    return l;
}

void freeStringsList(List *l)
{
    for (int i = 0; i < List_size(l); i++)
    {
        char *item = List_get(l, i);
        free(item);
    }
    List_deinit(l);
}

void printStringsList(List *l)
{
    for (int i = 0; i < List_size(l); i++)
    {
        char *vp = List_get(l, i);
        printf("\"%s\", ", vp);
    }
    printf("\n");
}

void printStringsTable(List *table)
{
    for (int i = 0; i < List_size(table); i++)
    {
        List *row = List_get(table, i);
        printStringsList(row);
    }
}

void freeStringsTable(List *table)
{
    for (int i = 0; i < List_size(table); i++)
    {
        List *row = List_get(table, i);
        freeStringsList(row);
        free(row);
    }
    List_deinit(table);
}

int main()
{
    char *lines[][3] = {
        {
            "Hi",
            "Hej",
            "Hola",
        },
        {
            "2",
            "3",
            "4",
        },
        {
            "a",
            "b",
            "c",
        }};
    int linesWidth = 3;
    int linesHeight = sizeof(lines) / sizeof(char * [3]);

    List table;
    List_init(&table);
    for (int i = 0; i < linesHeight; i++)
    {
        List lc = createList(linesWidth, lines[i]);
        List *pl = malloc(sizeof(List));
        *pl = lc;

        List_add(&table, pl);
    }
 
    printStringsTable(&table);

    freeStringsTable(&table);
    return 0;
}

int main0(int argc, char const *argv[])
{
    DynArray d;
    DynArray_init(&d);
    DynArray_deinit(&d);
    puts("Hi\n");
    assert(isBalanced("({]") == 0);
    assert(isBalanced("({}])") == 0);
    assert(isBalanced("(") == 0);
    assert(isBalanced("({") == 0);
    assert(isBalanced("({}") == 0);
    assert(isBalanced(")()") == 0);
    assert(isBalanced(")()(") == 0);
    assert(isBalanced("({})[]") == 1);
    assert(isBalanced("({[]})") == 1);
    assert(isBalanced("({[]()})") == 1);
    assert(isBalanced("(){}[]") == 1);

    return 0;
}

int typeEquals(char a, char b)
{
    if (a == '(' && b == ')')
        return 1;
    if (a == '{' && b == '}')
        return 1;
    if (a == '[' && b == ']')
        return 1;
    return 0;
}

int isBalanced(const char *str)
{
    Stack stack;
    Stack_init(&stack);

    const char *p = str;
    while (*p != '\0')
    {
        if (strchr("([{", *p))
        {
            Stack_push(&stack, *p);
        }
        else
        {
            if (typeEquals(Stack_peek(&stack), *p))
            {
                Stack_pop(&stack);
            }
            else
            {
                Stack_deinit(&stack);
                return 0;
            }
        }
        p += 1;
    }
    int result = 0;
    if (Stack_size(&stack) == 0)
    {
        result = 1;
    }
    Stack_deinit(&stack);
    return result;
}
