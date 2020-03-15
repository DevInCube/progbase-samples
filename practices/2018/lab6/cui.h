#pragma once

#include "storage.h"

class Cui
{
    Storage * const storage_;

    // students menus
    void studentsMain();
    void studentsAll();
    void studentSingle(int entity_id);
    void studentCreate();
    
public:
    Cui(Storage * storage): storage_(storage) {}
    //
    void show();
};

void Cui::show()
{
    studentsMain();
}

void Cui::studentsMain()
{
    std::cout << "\nget all" << std::endl;
    vector<Student> students = storage_->getAllStudents();
    for (Student &st : students)
    {
        print(st);
    }
}