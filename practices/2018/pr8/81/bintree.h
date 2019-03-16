#pragma once 

typedef struct 
{
    int id;
    char fullname[100];
} Student;

int Student_key(Student st);

typedef struct __BinTree BinTree;
struct __BinTree 
{
   int key;
   Student value;      // set on init/alloc
   BinTree * left;  // set to NULL on init
   BinTree * right; // set to NULL on init
};

BinTree * BinTree_alloc (Student value);
void   BinTree_free     (BinTree * self);