#pragma once

#include "student.h"

typedef struct __BinTree BinTree;
struct __BinTree 
{
   int key;
   Student value;      // set on init/alloc
   BinTree * left;  // set to NULL on init
   BinTree * right; // set to NULL on init
};

void   BinTree_init     (BinTree * self, Student value);
void   BinTree_deinit   (BinTree * self);

BinTree * BinTree_alloc (Student value);
void   BinTree_free     (BinTree * self);