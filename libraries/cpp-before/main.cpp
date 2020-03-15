#include <iostream>
#include "list.h"

using namespace std;

int main()
{
    ruslan::List list;
    list.push_back(15);
    list.push_back(-9);

    for (int i = 0; i < list.size(); i++)
    {
        cout << list[i] << endl;
    }
}