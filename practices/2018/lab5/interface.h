#pragma once

#include <vector>
#include <string>

#include "optional.h"
#include "student.h"
#include "course.h"
#include "csv.h"

using std::string;
using std::vector;

class Storage
{
    const char *dir_name_;

    vector<Student> students_;
    vector<Course> courses_;

    Student rowToStudent(const vector<string> &row);
    vector<string> studentToRow(const Student &st);
    Course rowToCourse(const vector<string> &row);
    vector<string> courseToRow(const Course &st);

    int getNewStudentIndex();
    int getNewCourseIndex();

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
    // courses
    vector<Course> getAllCourses(void);
    optional<Course> getCourseById(int id);
    bool updateCourse(const Course &course);
    bool removeCourse(int course_id);
    int insertCourse(const Course &course);
};