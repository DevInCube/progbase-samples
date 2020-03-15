#include "list.h" // generic list (array implementation)
#include "csv.h"
#include "composer.h"
#include <ctype.h>

void invalidArgumentError(char *argv);
int argNreader(char *argv[], int i);
void argOreader(char *argv[], int i, char *output);
void noArgumentsError(char *argv);

void processItems(List *items, int N, bool tableFromTestString);

void fillListOfStructsFromTable(List *inCsvTable, List *composers);
void fillTableFromListOfStructs(List *outCsvTable, List *composers);
void fillListOfStructsFromTestString(List *composers, Composer testList[], int testListlength);

void printListOfStructs(List *self);

void recordToOutputFile(FILE *fl, List *outCsvTable);
void readFileToBuf(FILE *fp, char *buf);

int main(int argc, char *argv[])
{
    Composer testList[] = {
        {1, "Johann Bach", 1721, "Brandenburg Concertos", 1126},
        {2, "Wolfgang Mozart", 1783, "Turkish stop", 498},
        {3, "Ludwig van Beethoven", 1801, "Moonlight Sonata", 122},
        {4, "Richard Wagner", 1856, "Ride of the Valkyries", 56},
    };
    int testListlength = 4;

    char output[100];
    char input[] = "data.csv";

    bool wasInputFile = false;
    bool wasArgAfterN = false;
    bool wasArgAfterO = false;
    bool tableFromTestString = false;

    int N = 0;

    //reading arguments from console
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "data.csv") == 0)
        {
            wasInputFile = true;
        }
        else if (argv[i][0] == '-')
        {
            {
                int j = 1;
                switch (argv[i][j])
                {
                    //--
                case 'n':
                {
                    if (i != argc - 1)
                        i++;
                    else
                    {
                        noArgumentsError(argv[i]);
                    }
                    N = argNreader(argv, i);

                    wasArgAfterN = true;

                    break;
                }
                case 'o':
                {
                    if (i != argc - 1)
                        i++;
                    else
                    {
                        noArgumentsError(argv[i]);
                    }

                    argOreader(argv, i, output);

                    wasArgAfterO = true;

                    break;
                }
                default:
                {
                    invalidArgumentError(argv[i]);
                    break;
                }
                    //--
                }
            }
        }
    }
    //

    if (wasArgAfterO == false)
    {
        strcpy(output, "output.txt");
    }

    List inCsvTable;
    List_init(&inCsvTable);

    List composers;
    List_init(&composers);

    if (wasInputFile)
    {
        FILE *fp = fopen(input, "r");

        if (fp == NULL)
        {
            printf("\n---------File == NULL. Aborted-----\n");
            fclose(fp);
            List_deinit(&inCsvTable);
            List_deinit(&composers);
            abort();
        }
        
        char buf[500];
        readFileToBuf(fp, buf);
        if (fp != NULL)
        {
            fclose(fp);
        }

        Csv_fillTableFromString(&inCsvTable, buf);
        puts("\n------------------inCsvTable-----------------------------\n");
        printfStringsTable(&inCsvTable);

        fillListOfStructsFromTable(&inCsvTable, &composers);
    }
    else
    {
        fillListOfStructsFromTestString(&composers, testList, testListlength);
        tableFromTestString = true;
    }

    if (wasArgAfterN)
    {
        processItems(&composers, N, tableFromTestString);
    }

    List outCsvTable;
    List_init(&outCsvTable);

    fillTableFromListOfStructs(&outCsvTable, &composers);
    puts("\n\n------------------outCsvTable-----------------------------\n");

    printfStringsTable(&outCsvTable);
    puts(" ");

    if (wasArgAfterO)
    {
        FILE *fl;
        fl = fopen(output, "w");
        recordToOutputFile(fl, &outCsvTable);
        fclose(fl);
    }

    if (wasInputFile)
    {
        for (int i = 0; i < List_size(&composers); i++)
        {
            Composer *pSt = static_cast<Composer*>(List_get(&composers, i));
            free(pSt);
        }
    }
    List_deinit(&composers);

    Csv_clearTable(&outCsvTable);
    List_deinit(&outCsvTable);

    Csv_clearTable(&inCsvTable);
    List_deinit(&inCsvTable);

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

void processItems(List *composers, int N, bool tableFromTestString)
{
    for (int i = 0; i < List_size(composers); i++)
    {
        Composer *com;
        com = static_cast<Composer*>(List_get(composers, i));

        if (com->amount < N)
        {
            List_removeAt(composers, i);
            if (tableFromTestString != true)
            {
                free(com);
            }
            i -= 1;
        }
    }
}

void fillListOfStructsFromTable(List *inCsvTable, List *composers)
{
    for (int i = 0; i < List_size(inCsvTable); i++)
    {
        List *row = static_cast<List*>(List_get(inCsvTable, i));
        Composer *com = static_cast<Composer*>(malloc(sizeof(Composer)));

        com->id = Csv_int(row, 0);
        Csv_stringCopyToBuf(row, 1, com->fullname);
        com->year = Csv_int(row, 2);
        Csv_stringCopyToBuf(row, 3, com->winner);
        com->amount = Csv_int(row, 4);

        List_add(composers, com);
    }
}

void fillTableFromListOfStructs(List *outCsvTable, List *composers)
{
    for (int i = 0; i < List_size(composers); i++)
    {
        Composer *pSt = static_cast<Composer*>(List_get(composers, i));

        List *pRow = List_alloc();

        Csv_addInt(pRow, pSt->id);
        Csv_addString(pRow, pSt->fullname);
        Csv_addInt(pRow, pSt->year);
        Csv_addString(pRow, pSt->winner);
        Csv_addInt(pRow, pSt->amount);

        Csv_addRow(outCsvTable, pRow);
    }
}

void fillListOfStructsFromTestString(List *composers, Composer testList[], int testListlength)
{
    for (int i = 0; i < testListlength; i++)
    {
        List_add(composers, &testList[i]);
    }
}

void Csv_printListOfStructs(List *self)
{
    for (int i = 0; i < List_size(self); i++)
    {
        Composer *comRow = static_cast<Composer*>(List_get(self, i));

        printf("%d,", comRow->id);
        printf("%s,", comRow->fullname);
        printf("%d,", comRow->year);
        printf("%s,", comRow->winner);
        printf("%d\n", comRow->amount);
    }
}

void readFileToBuf(FILE *fp, char *buf)
{
    size_t buf_i = 0;
    if (fp != NULL)
    {
        char ch = fgetc(fp);
        while (1)
        {
            if (ch == EOF)
            {
                break;
            }

            buf[buf_i] = ch;
            ch = fgetc(fp);
            buf_i++;
        }
        buf[buf_i] = '\0';
    }
}

void recordToOutputFile(FILE *fl, List *outCsvTable)
{
    if (fl != NULL) 
    {
        for (int i = 0; i < List_size(outCsvTable); i++)
        {
            List *rowItem = static_cast<List*>(List_get(outCsvTable, i));
            for (int j = 0; j < List_size(rowItem); j++)
            {
                char *value = static_cast<char*>(List_get(rowItem, j));
                fprintf(fl, "%s", value);
                if (j != List_size(rowItem) - 1)
                {
                    fprintf(fl, ",");
                }
            }
            if (i != List_size(outCsvTable) - 1)
            {
                fprintf(fl, "\n");
            }
        }
    }
}