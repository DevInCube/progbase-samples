#pragma once

typedef struct {
    int id;
    char fullname[100];
} Student;

int Student_key(Student st);