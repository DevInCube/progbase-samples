#pragma once

#include <vector>
#include <string>

#include "optional.h"
#include "student.h"
#include "csv.h"

using std::string;
using std::vector;

class Storage
{
    const char *dir_name_;

    vector<Student> students_;

    Student rowToStudent(const vector<string> &row);
    vector<string> studentToRow(const Student &st);

    int getNewStudentIndex();

  public:
    Storage(const char *dir_name);

    void load();
    void save();
    // students
    vector<Student> getAllStudents(void);
    optional<Student> getStudentById(int id);
    bool updateStudent(const Student &student);
    bool removeStudent(int student_id);
    int insertStudent(const Student &student);
};