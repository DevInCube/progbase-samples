#include <cmath>
#include <iostream>
#include <string>
#include "list.h"
#include "stack.h"
#include <vector>

using namespace std;

void List_print(List & ((self)));

#include <algorithm>
#include <sstream>

int main()
{
    std::stringstream ss;
    ss << "Hi " << 5 << std::endl;
    std::cout << ss.str();

vector<int> vec = {0, 1, 2, 3, 4};
vector<int>::iterator it_begin = vec.begin();
vector<int>::iterator it_end = vec.end();
vector<int>::const_iterator const_it_begin = vec.cbegin();
vector<int>::const_iterator const_it_end = vec.cend();
std::reverse_iterator<vector<int>::iterator> it_begin_rev = vec.rbegin();
std::reverse_iterator<vector<int>::iterator> it_end_rev = vec.rend();
std::reverse_iterator<vector<int>::const_iterator> const_it_begin_rev = vec.crbegin();
std::reverse_iterator<vector<int>::const_iterator> const_it_end_rev = vec.crend();

for (int item : {1, 2, 3, 5}) 
{
    // Access element value copy
    cout << item << " ";
}
for (int & item : vec) 
{
    // Access element value reference
    cout << item << " ";
}
for (auto item : vec) 
{
    // Access element value copy
    cout << item << " ";
}
for (auto & item : vec) 
{
    // Access element value reference
    cout << item << " ";
}
    return 0;

    List list;
    //(*list)[3]

    list.clear();

    //reading from file
    char buf[100];
    int buf_i = 0;

    FILE *fin = fopen("data.txt", "r");
    if (fin == NULL) {
        fprintf(stderr, "File not found\n");
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
    //

    puts("\n--------------->>First list----------------------");
    List_print(list);

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
    puts("\n--------------->>Numbers greater than 10 moved to the top of list------");
    List_print(list);
    //
    return 0;
}

void List_print(List  & self)
{
    for (int i = 0; i < self.size(); i++)
    {
        printf(" %.3f ", self[i]);
    }
    puts(" ");
}
