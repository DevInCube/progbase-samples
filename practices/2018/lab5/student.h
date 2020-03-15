#pragma once

#include <string>
#include <iostream>

struct Student 
{
    int id;
    std::string fullname;
    std::string group;
    float score;
};

void print(Student & st)
{
    std::cout << st.id << " | " 
        << st.fullname << " | " 
        << st.group << " | " 
        << st.score << std::endl;
}