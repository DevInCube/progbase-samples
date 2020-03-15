#include "csv.h"

// parse csv, create & fill string table
CsvTable Csv::createTableFromString(const string &csv_str)
{
    const char *p = csv_str.c_str();
    char buf[500];
    int bufX = 0;
    CsvRow csv_row;
    CsvTable csv_table;
    while (1)
    {
        if (*p == ',' || *p == '\n' || *p == '\0')
        {
            buf[bufX] = '\0';
            if (*p != '\0' && bufX > 0)
            {
                string value = buf;
                csv_row.push_back(value);
                //Csv_addString(rowTable, buf);
            }
            if (*p == '\n')
            {
                if (csv_row.size() > 0)
                    csv_table.push_back(csv_row);
                //Csv_addRow(csvTable, rowTable);
                csv_row.clear();
                //rowTable = List_alloc();
            }
            else if (*p == '\0')
            {
                if (csv_row.size() > 0)
                    csv_table.push_back(csv_row);
                //Csv_addRow(csvTable, rowTable);
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
    return csv_table;
}

// return a string filled with csv from string table
string Csv::createStringFromTable(const CsvTable &csv_table)
{
    string csv_text;
    for (int i = 0; i < csv_table.size(); i++) 
    {
        const CsvRow & row  = csv_table.at(i);
        // List *rowItem = static_cast<List*>(List_get(csvTable, i));
        for (int j = 0; j < row.size(); j++)
        {
            const string & value  = row.at(j);
            //char *value = static_cast<char*>(List_get(rowItem, j));
            // strcat(buf, value);
            csv_text += value;
            if (j != row.size() - 1)
            {
                //strcat(buf, ",");
                csv_text += ",";
            }
        }
        if (i != csv_table.size() - 1)
        {
            csv_text += "\n";
            //strcat(buf, "\n");
        }
    }
    return csv_text;
}

// int Csv_fillStringFromTable(List *csvTable, char *buf) // fill buf with csv
// {
//     buf[0] = '\0';
//     for (int i = 0; i < List_size(csvTable); i++)
//     {
//         List *rowItem = static_cast<List*>(List_get(csvTable, i));
//         for (int j = 0; j < List_size(rowItem); j++)
//         {
//             char *value = static_cast<char*>(List_get(rowItem, j));
//             strcat(buf, value);
//             if (j != List_size(rowItem) - 1)
//             {
//                 strcat(buf, ",");
//             }
//         }
//         if (i != List_size(csvTable) - 1)
//         {
//             strcat(buf, "\n");
//         }
//     }
//     return 0;
// }
// char *Csv_createStringFromTable(List *csvTable) // malloc string array and fill it with csv
// {
//     char *buf = (char *)" ";
//     buf = strOnHeap(buf);
//     Csv_fillStringFromTable(csvTable, buf);
//     return buf;
// }


// void printfStrings(List *self)
// {
//     for (int i = 0; i < List_size(self); i++)
//     {
//         char *item = static_cast<char*>(List_get(self, i));
//         printf("| %s |", item);
//     }
//     puts(" ");
// }