#include "student.h"

student::student()
{
    this->_age = 0;
    this->_name = "";
    this->_surname = "";
}

student::~student()
{
    std::cout << "Student is destoyed!" << std::endl;
}

void student::set_name(string name) { this->_name = name; }
void student::set_surname(string surname) { this->_surname = surname; }
void student::set_age(int age) { this->_age = age; }

string student::name() { return this->_name; }
string student::surname() { return this->_surname; }
int student::age() { return this->_age; }

void student::print() {
    std::cout << _name << " | " << _surname << " | " << _age << std::endl;
}
