#include "list.h"
#include <progbase/console.h>
#include <cmath>
#include <iostream>
#include <string>

void List_print(List & self);
List List_readFromFile(const char * filename)
{
    List list;
    //reading from file
    char buf[100];
    int buf_i = 0;
    FILE *fin = fopen(filename, "r");
    if (fin == NULL) {
        fprintf(stderr, "file not found\n");
        abort();
    }
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

void List_sort(List & list)
{
    float num = 0;
    int firts_position = 0;
    int length = list.size();
    for (int i = 0; i < length; i++)
    {
        num = list[i];
        if (fabs(num) > 10)
        {
            list.removeAt(i);
            list.insert(firts_position, num);
        }
    }
}

int main()
{   
    List list;
    // List list();
    List list = List();
    List list{};
    List list = List{};

    List * p = new List;
    List * p = new List();
    List * p = new List{};


    std::string str = "34";
    int val = std::stoi(str);
    std::cout << val;
    //std::cin >> str;
    // std::getline(std::cin, str);
    std::cout << str << std::endl;
    str += "Hi";
    str.insert(1, "Google");
    std::cout << str.length() << std::endl;
    std::cout << str << std::endl;
    
    // List list = List_readFromFile("data.txt");
    // List_print(list);
    // List_sort(list);
    
    // char new_val[100] = "asd";
    // new_val = "asd";
    //std::cin >> new_val;  
    //std::getline(std::cin, new_val);
    //std::cout << new_val << std::endl;
    // List_print(list);
    return 0;
}
//
void List_print(List & list)
{
    for (int i = 0; i < list.size(); i++)
    {
        float & item = list[i];
        std::cout << " " << item << " ";
        // printf(" %.3f ", item);
    }
    std::cout << " " << std::endl;
}