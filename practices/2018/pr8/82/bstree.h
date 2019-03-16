#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include "bintree.h"



typedef struct __BSTree BSTree;
struct __BSTree 
{
    BinTree * root;  // a pointer to the root tree node
};

void BSTree_init(BSTree * self);
void BSTree_deinit(BSTree * self); 

size_t BSTree_size     (BSTree * self);  // number of stored values

// int getKey(TValue value);  // there should be a function to get key from value

void   BSTree_insert   (BSTree * self, Student value);  // add unique
bool   BSTree_lookup   (BSTree * self, int key);  // check for value with a key
Student * BSTree_search   (BSTree * self, int key);  // get the value for a key
Student BSTree_delete   (BSTree * self, int key);  // delete the value for a key
void   BSTree_clear    (BSTree * self);           // delete all values
