#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "optional.h"
#include "student.h"
#include "course.h"

#include "storage.h" 

using namespace std;

struct StudentToCourse
{
    int id;
    int student_id;
    int course_id;
};

class CsvStorage : public Storage
{
    const string dir_name_;
    vector<Student> students_;
    vector<Course> courses_;
    vector<StudentToCourse> links_;

    vector<vector<string>> parseCsv(ifstream &f)
    {
        if (f.bad())
            abort();
        vector<vector<string>> table;
        string line;
        while (getline(f, line))
        {
            vector<string> row;
            stringstream ss(line);
            string value;
            while (getline(ss, value, ','))
            {
                row.push_back(value);
            }
            table.push_back(row);
        }
        return table;
    }

    Student rowToStudent(vector<string> &row)
    {
        Student st;
        st.id = stoi(row[0]);
        st.fullname = row[1];
        st.group = row[2];
        st.score = stof(row[3]);
        return st;
    }

    Course rowToCourse(vector<string> &row)
    {
        Course st;
        st.id = stoi(row[0]);
        st.title = row[2];
        return st;
    }

    int getNewStudentIndex()
    {
        return -1; // @todo
    }

    int getNewCourseIndex()
    {
        return -1; // @todo
    }

  public:
    CsvStorage(const string & dir_name)
        : dir_name_(dir_name)
    {
        
    }

    bool load()
    {
        ifstream f;
        f.open(string(dir_name_) + "/students.csv");
        auto table = parseCsv(f);
        f.close();
        for (auto &row : table)
        {
            Student st = rowToStudent(row);
            this->students_.push_back(st);
        }
        f.open(string(dir_name_) + "/courses.csv");
        table = parseCsv(f);
        f.close();
        for (auto &row : table)
        {
            Course cs = rowToCourse(row);
            this->courses_.push_back(cs);
        }
        f.open(string(dir_name_) + "/student_to_course.csv");
        table = parseCsv(f);
        f.close();
        for (auto &row : table)
        {
            StudentToCourse stc;
            stc.id = stoi(row[0]);
            stc.student_id = stoi(row[1]);
            stc.course_id = stoi(row[2]);
            this->links_.push_back(stc);
        }
        return true;
    }
    bool save()
    {
        ofstream f;
        f.open(string(dir_name_) + "/students.csv");
        for (auto &st : this->students_)
        {
            f << st.id << ","
              << st.fullname << ","
              << st.group << ","
              << st.score << endl;
        }
        f.close();

        // @todo save courses
        // @todo save links
        return false;
    }

    vector<Student> getAllStudents(void)
    {
        return this->students_;
    }

    optional<Student> getStudentById(int id)
    {
        for (auto &st : this->students_)
        {
            if (st.id == id)
            {
                return st;
            }
        }
        return nullopt;
    }
    bool updateStudent(const Student &student)
    {
        for (auto &st : this->students_)
        {
            if (st.id == student.id)
            {
                st.fullname = student.fullname;
                st.group = student.group;
                st.score = student.score;
                return true;
            }
        }
        return false;
    }
    bool removeStudent(int student_id)
    {
        int index = -1;
        for (int i = 0; i < this->students_.size(); i++)
        {
            if (this->students_[i].id == student_id)
            {
                index = i;
                break;
            }
        }
        if (index == -1)
        {
            return false;
        }
        this->students_.erase(this->students_.begin() + index);
        return true;
    }
    int insertStudent(const Student &student)
    {
        int new_index = getNewStudentIndex();
        Student copy = student;
        copy.id = new_index;
        this->students_.push_back(copy);
        return new_index;
    }
    // courses
    vector<Course> getAllCourses(void)
    {
        return this->courses_;
    }
    optional<Course> getCourseById(int id)
    {
        for (auto &cs : this->courses_)
        {
            if (cs.id == id)
            {
                return cs;
            }
        }
        return nullopt;
    }
    int insertCourse(const Course &course)
    {
        int new_index = getNewCourseIndex();
        Course copy = course;
        copy.id = new_index;
        this->courses_.push_back(copy);
        return new_index;
    }
    bool updateCourse(const Course &course) {}
    bool removeCourse(int course_id) {}
    // links
    vector<Course> getAllStudentCourses(int student_id)
    {
        vector<Course> courses;
        for (auto & link: links_)
        {
            if (link.student_id == student_id)
            {
                auto courseopt = this->getCourseById(link.course_id);
                // @todo if !courseopt
                courses.push_back(courseopt.value());
            }
        }
        return courses;
    }
    void insertStudentCourse(int student_id, int course_id)
    {
        StudentToCourse link;
        link.id = -1; // @todo
        link.student_id = student_id;
        link.course_id = course_id;
        this->links_.push_back(link);
    }
    
};