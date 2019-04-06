#include "list.h"
#include <progbase/console.h>
#include <cmath>
#include <iostream>
#include <cassert>

void print(List *self);
List readFloatsFromFile(const char *fileName);
void processList(List * list);

int main()
{
    Console_clear(); 
    std::cout << " >>>--------------------List-----------------------\n" << std::endl;
    List list = readFloatsFromFile("data.txt");
    //list[0] = 13;  
    //std::cout << "[0] " << list[0] << std::endl;
    print(&list);
    puts("\n--------------->>Numbers greater than 10 moved to the top of list------");
    print(&list);
    return 0;
}
//
void print(List *self)
{
    for (int i = 0; i < self->size(); i++)
    {
        printf(" %.3f ", (*self)[i]);
    }
    puts(" ");
}

List readFloatsFromFile(const char *fileName)
{
    List list;
    //reading from file
    char buf[100];
    int buf_i = 0;

    FILE *fin = fopen("data.txt", "r");
    char ch = fgetc(fin);

    while (1)
    {
        if (ch == ' ' || ch == EOF)
        {
            buf[buf_i] = '\0';
            buf_i = 0;
            float curr_num = atof(buf);
            if (buf[0] != '\0')
            {
                list.add(curr_num);
            }
        }
        else
        {
            buf[buf_i++] = ch;
        }
        if (ch == EOF)
        {
            break;
        }
        ch = fgetc(fin);
    }
    if (fin != NULL)
    {
        fclose(fin);
    }
    return list;
}

void processList(List * list)
{
    float num = 0;
    int firts_position = 0;
    int length = list->size();
    for (int i = 0; i < length; i++)
    {
        num = (*list)[i];
        if (fabs(num) > 10)
        {
            list->removeAt(i);
            list->insert(firts_position, num);
        }
    }
}