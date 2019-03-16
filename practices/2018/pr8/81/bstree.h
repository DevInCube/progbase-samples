#pragma once

#include "bintree.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct __BSTree BSTree;
struct __BSTree
{
    BinTree * root;
};

void BSTree_init(BSTree *self);
void BSTree_deinit(BSTree *self);

void BSTree_print(BSTree * self);

void BSTree_insert(BSTree * self, Student value);
bool BSTree_lookup(BSTree * self, int key); 
Student * BSTree_search(BSTree * self, int key);
Student * BSTree_delete(BSTree * self, int key);

void clearTree(BinTree * node);