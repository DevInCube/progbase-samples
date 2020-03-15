#include "csv.h"
#include "composer.h"
#include <ctype.h>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

void invalidArgumentError(char *argv);
int argNreader(char *argv[], int i);
void argOreader(char *argv[], int i, char *output);
void noArgumentsError(char *argv);

void printfStringsTable(CsvTable & table);

void readFileToBuf(FILE *fp, char *buf);


#include "storage.h"
#include "cui.h"

int main(int argc, char *argv[])
{
    Storage storage("./data");
    storage.load();

    Cui cui(&storage);
    cui.show();
    return 0;
}

//

void invalidArgumentError(char *argv)
{
    fprintf(stderr, "Error: invalid argument  '%s'  \n", argv);
    abort();
}

void noArgumentsError(char *argv)
{
    fprintf(stderr, "Error: no arguments after %s \n", argv);
    abort();
}

int argNreader(char *argv[], int i)
{
    int N = 0;
    char buf[100];
    int bufX = 0;
    //
    for (int j = 0; j < strlen(argv[i]); j++)
    {
        if (isdigit(argv[i][j]))
        {
            buf[bufX] = argv[i][j];
            bufX++;
        }
        else
        {
            if (argv[i][j] == '-')
                noArgumentsError(argv[i - 1]);
            else
                invalidArgumentError(argv[i]);
        }
    }
    buf[bufX] = '\0';
    N = atoi(buf);
    bufX = 0;
    return N;
}

void argOreader(char *argv[], int i, char *output)
{
    char bufO[100];
    int bufx = 0;
    for (int k = 0; k < strlen(argv[i]); k++)
    {
        bufO[bufx] = argv[i][k];
        bufx++;
    }
    bufO[bufx] = '\0';
    bufx = 0;
    strcpy(output, bufO);
}


// void fillListOfStructsFromTable(List *inCsvTable, List *composers)
// {
//     for (int i = 0; i < List_size(inCsvTable); i++)
//     {
//         List *row = static_cast<List*>(List_get(inCsvTable, i));
//         Composer *com = static_cast<Composer*>(malloc(sizeof(Composer)));

//         com->id = Csv_int(row, 0);
//         Csv_stringCopyToBuf(row, 1, com->fullname);
//         com->year = Csv_int(row, 2);
//         Csv_stringCopyToBuf(row, 3, com->winner);
//         com->amount = Csv_int(row, 4);

//         List_add(composers, com);
//     }
// }

// void fillTableFromListOfStructs(List *outCsvTable, List *composers)
// {
//     for (int i = 0; i < List_size(composers); i++)
//     {
//         Composer *pSt = static_cast<Composer*>(List_get(composers, i));

//         List *pRow = List_alloc();

//         Csv_addInt(pRow, pSt->id);
//         Csv_addString(pRow, pSt->fullname);
//         Csv_addInt(pRow, pSt->year);
//         Csv_addString(pRow, pSt->winner);
//         Csv_addInt(pRow, pSt->amount);

//         Csv_addRow(outCsvTable, pRow);
//     }
// }

// void fillListOfStructsFromTestString(List *composers, Composer testList[], int testListlength)
// {
//     for (int i = 0; i < testListlength; i++)
//     {
//         List_add(composers, &testList[i]);
//     }
// }


// void readFileToBuf(FILE *fp, char *buf)
// {
//     size_t buf_i = 0;
//     if (fp != NULL)
//     {
//         char ch = fgetc(fp);
//         while (1)
//         {
//             if (ch == EOF)
//             {
//                 break;
//             }

//             buf[buf_i] = ch;
//             ch = fgetc(fp);
//             buf_i++;
//         }
//         buf[buf_i] = '\0';
//     }
// }

// void recordToOutputFile(FILE *fl, List *outCsvTable)
// {
//     if (fl != NULL) 
//     {
//         for (int i = 0; i < List_size(outCsvTable); i++)
//         {
//             List *rowItem = static_cast<List*>(List_get(outCsvTable, i));
//             for (int j = 0; j < List_size(rowItem); j++)
//             {
//                 char *value = static_cast<char*>(List_get(rowItem, j));
//                 fprintf(fl, "%s", value);
//                 if (j != List_size(rowItem) - 1)
//                 {
//                     fprintf(fl, ",");
//                 }
//             }
//             if (i != List_size(outCsvTable) - 1)
//             {
//                 fprintf(fl, "\n");
//             }
//         }
//     }
// }

// void printfStrings(vector<string> & self)
// {
//     for (int i = 0; i < self.size(); i++)
//     {
//         printf("| %s |", self[i].c_str());
//     }
//     puts(" ");
// }

void printfStringsTable(CsvTable & table)
{
    for (int i = 0; i < table.size(); i++)
    {
        CsvRow row = table[i];
        for (int j = 0; j < row.size(); j++)
        {
            if (i == 0 && j == 0)
            {
                printf("%s", row[j].c_str());
            }
            else if (i != 0 && j == 0)
            {
                printf("%s", row[j].c_str());
            }
            else
            {
                printf(",");
                printf("%s", table[i][j].c_str());
            }
        }
        printf("\n");
    }
}