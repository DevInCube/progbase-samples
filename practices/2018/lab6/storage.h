#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "optional.h"
#include "student.h"
#include "course.h"

using namespace std;

class Storage
{
  public:
    virtual bool load() = 0;
    virtual bool save() = 0;
    // students
    virtual vector<Student> getAllStudents(void) = 0;
    virtual optional<Student> getStudentById(int student_id) = 0;
    virtual bool updateStudent(const Student &student) = 0;
    virtual bool removeStudent(int student_id) = 0;
    virtual int insertStudent(const Student &student) = 0;
    // courses
    virtual vector<Course> getAllCourses(void) = 0;
    virtual optional<Course> getCourseById(int course_id) = 0;
    virtual bool updateCourse(const Course &course) = 0;
    virtual bool removeCourse(int course_id) = 0;
    virtual int insertCourse(const Course &course) = 0;
};