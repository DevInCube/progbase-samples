#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>

using namespace std;

class student
{
    string _name;
    string _surname;
    int _age;
public:
    student();
    ~student();

    void set_name(string name);
    void set_surname(string surname);
    void set_age(int age);

    string name();
    string surname();
    int age();

    void print();
};

#endif // STUDENT_H
