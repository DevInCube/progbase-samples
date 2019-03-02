#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "list.h"

void printStrings(List *pl);
void printTable(List *pl);

char *strOnHeap(const char *str)
{
    char *m = malloc(strlen(str) + 1);
    strcpy(m, str);
    return m;
}

void Csv_fillTableFromString(List *csvTable, const char *csvString);
int Csv_fillStringFromTable(List *csvTable, char *b, int n);
void Csv_clearTable(List *csvTable);

void printInt(int num) { printf("%i, ", num); }

void printIntBraced(int num) { printf("[%i]", num); }

void printArray(
    int size, 
    int items[size], 
    void (*printer)(int)
    )
{
    for (int i = 0; i < size; i++)
    {
        printer(items[i]);
    }
}

int main() 
{
    int arr[] = {1, 5, -3, 67, 100};
    printArray(5, arr, printIntBraced);
    printArray(5, arr, printInt);
    return 0;
}


int main0()
{
    List table;
    List_init(&table);
    // @todo read from file
    const char *input = "12,John Wick,KP-99,100\n33,Jude Law,KP-98,99.5\n";
    //
    Csv_fillTableFromString(&table, input);
    //
    char buf[1000];
    Csv_fillStringFromTable(&table, buf, 1000);
    puts(buf);
    // print
    // for (int i = 0; i < List_size(&table); i++)
    // {
    //     List * rowItem = List_get(&table, i);
    //     for (int j = 0 ; j < List_size(rowItem); j++)
    //     {
    //         char * value = List_get(rowItem, j);
    //         printf("[%s]", value);
    //     }
    //     printf("\n");
    // }
    // cleanup
    Csv_clearTable(&table);
    //
    List_deinit(&table);
    return 0;
}

void Csv_fillTableFromString(List *csvTable, const char *csvString)
{
    List *row = NULL;
    char buf[100];
    int bufX = 0;
    const char *p = csvString;
    while (1)
    {
        if (*p == ',' || *p == '\n' || *p == '\0')
        {
            buf[bufX] = '\0';
            if (bufX == 0 && *p == '\0' && row == NULL)
            {
                break;
            }
            if (row == NULL)
            {
                row = List_alloc();
            }
            List_add(row, strOnHeap(buf));
            //printf("[%s]", buf);  // end-of-value
            if (*p == '\n' || *p == '\0')
            {
                List_add(csvTable, row);
                row = NULL;
                //printf("\n");  // end-of-row
            }
            //
            bufX = 0;
        }
        else
        {
            buf[bufX] = *p;
            bufX += 1;
        }

        //
        if (*p == '\0')
        {
            break;
        }
        p += 1;
    }
}

void Csv_clearTable(List *csvTable)
{
    for (int i = 0; i < List_size(csvTable); i++)
    {
        List *rowItem = List_get(csvTable, i);
        for (int j = 0; j < List_size(rowItem); j++)
        {
            char *value = List_get(rowItem, j);
            free(value);
        }
        List_free(rowItem);
    }
}

int Csv_fillStringFromTable(List *csvTable, char *b, int n)
{
    b[0] = '\0';
    for (int i = 0; i < List_size(csvTable); i++)
    {
        List *rowItem = List_get(csvTable, i);
        for (int j = 0; j < List_size(rowItem); j++)
        {
            char *value = List_get(rowItem, j);
            strcat(b, value);
            if (j != List_size(rowItem) - 1)
            {
                strcat(b, ",");
            }
        }
        if (i != List_size(csvTable) - 1)
        {
            strcat(b, "\n");
        }
    }
    return 0;
}