#include "list.h" // generic list (array implementation)
#include "csv.h"

void Csv_addInt(List *row, int value) // malloc a string and write value in it
{
    char *str = static_cast<char*>(malloc(sizeof(char) * 10));
    sprintf(str, "%d", value);
    List_add(row, str);
}
void Csv_addDouble(List *row, double value) // malloc a str and write value in it
{
    char *str = static_cast<char*>(malloc(sizeof(char) * 10));
    sprintf(str, "%lf", value);
    List_add(row, str);
}
void Csv_addString(List *row, const char *value) // malloc a string and copy value
{
    List_add(row, (void *)strOnHeap(value));
}

int Csv_int(List *row, int index) // get item (str) and convert it to int
{
    return atoi(static_cast<char*>(List_get(row, index)));
}
double Csv_double(List *row, int index) // get str and convert it to double
{
    return atof(static_cast<char*>(List_get(row, index)));
}
int Csv_stringCopyToBuf(List *row, int index, char *buf) // get str & copy it to buf //Csv_string
{
    char *str = static_cast<char*>(List_get(row, index));
    strcpy(buf, str);
    int length = strlen(buf);
    return length;
}

void Csv_addRow(List *table, List *row) // add row to table as an item
{
    List_add(table, row);
}

List *Csv_row(List *table, int index) // get item from table as List *
{
    return static_cast<List *>(List_get(table, index));
}

void Csv_fillTableFromString(List *csvTable, const char *csvStr)
{
    const char *p = csvStr;
    char buf[500];
    int bufX = 0;
    List *rowTable = List_alloc();
    while (1)
    {
        if (*p == ',' || *p == '\n' || *p == '\0')
        {
            buf[bufX] = '\0';
            Csv_addString(rowTable, buf);
            if (*p == '\n')
            {
                Csv_addRow(csvTable, rowTable);
                rowTable = List_alloc();
            }
            else if (*p == '\0')
            {
                Csv_addRow(csvTable, rowTable);
            }
            bufX = 0;
        }
        else
        {
            buf[bufX] = *p;
            bufX += 1;
        }
        if (*p == '\0')
        {
            break;
        }
        p += 1;
    }
}

int Csv_fillStringFromTable(List *csvTable, char *buf) // fill buf with csv
{
    buf[0] = '\0';
    for (int i = 0; i < List_size(csvTable); i++)
    {
        List *rowItem = static_cast<List*>(List_get(csvTable, i));
        for (int j = 0; j < List_size(rowItem); j++)
        {
            char *value = static_cast<char*>(List_get(rowItem, j));
            strcat(buf, value);
            if (j != List_size(rowItem) - 1)
            {
                strcat(buf, ",");
            }
        }
        if (i != List_size(csvTable) - 1)
        {
            strcat(buf, "\n");
        }
    }
    return 0;
}
char *Csv_createStringFromTable(List *csvTable) // malloc string array and fill it with csv
{
    char *buf = (char *)" ";
    buf = strOnHeap(buf);
    Csv_fillStringFromTable(csvTable, buf);
    return buf;
}
void Csv_clearTable(List *csvTable) // free all table allocated memory
{
    for (int i = 0; i < List_size(csvTable); i++)
    {
        List *rowItem = static_cast<List*>(List_get(csvTable, i));
        for (int j = 0; j < List_size(rowItem); j++)
        {
            char *value = static_cast<char*>(List_get(rowItem, j));
            free(value);
        }
        List_free(rowItem);
    }
}

char *strOnHeap(const char *str)
{
    char *m = static_cast<char*>(malloc(strlen(str) + 1));
    strcpy(m, str);
    return m;
}

void printfStrings(List *self)
{
    for (int i = 0; i < List_size(self); i++)
    {
        char *item = static_cast<char*>(List_get(self, i));
        printf("| %s |", item);
    }
    puts(" ");
}

void printfStringsTable(List *self)
{
    for (int i = 0; i < List_size(self); i++)
    {
        List *row = static_cast<List*>(List_get(self, i));
        for (int j = 0; j < List_size(row); j++)
        {
            if (i == 0 && j == 0)
            {
                printf("%s", (char *)List_get(row, j));
            }
            else if (i != 0 && j == 0)
            {
                printf("%s", (char *)List_get(row, j));
            }
            else
            {
                printf(",");
                printf("%s", (char *)List_get(static_cast<List*>(List_get(self, i)), j));
            }
        }
        printf("\n");
    }
}