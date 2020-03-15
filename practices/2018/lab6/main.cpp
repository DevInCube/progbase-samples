#include "storage.h"
#include "csv_storage.h"

#include "cui.h"

int main(int argc, char const *argv[])
{
    CsvStorage csv_storage("./data");
    Storage * storagePtr = &csv_storage;
    storagePtr->load();
 
    Cui cui(storagePtr);
    cui.show();

// std::cout << "\nget by id" << std::endl;
// optional<Student> student_opt = storage.getStudentById(564);
// if (student_opt)
// {
//     // a student was found
//     Student &student = student_opt.value();
//     print(student);

//     // modify
//     student.score = 101;
//     storage.updateStudent(student);
//     storage.removeStudent(-1);
//     Student newStudent;
//     newStudent.fullname = "new";
//     newStudent.group = "new";
//     newStudent.score = 0.0;
//     storage.insertStudent(newStudent);
//     storage.save();
// }

// vector<Course> courses = storage.getAllCourses();
// std::cout << "\nget all courses:" << std::endl;
// for (Course &cs : courses)
// {
//     print(cs);
// }

//     // links

//     Course newStudentCourse;
//     newStudentCourse.title = "Math";

//     newStudentCourse.id = storage.insertCourse(newStudentCourse);
//     storage.insertStudentCourse(12, newStudentCourse.id);

//     vector<Course> stcourses = storage.getAllStudentCourses(12);
//     std::cout << "\nget all student (12) courses:" << std::endl;
//     for (Course &cs : stcourses)
//     {
//         print(cs);
//     }
}
