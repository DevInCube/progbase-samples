#pragma once

#include <string>
#include <iostream>

struct Course
{
    int id;
    std::string title;
};

void print(Course & st)
{
    std::cout << st.id << " | " 
        << st.title << std::endl;
}