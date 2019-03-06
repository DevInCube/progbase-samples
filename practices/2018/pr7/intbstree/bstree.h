#pragma once

#include "intbintree.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct __BSTree BSTree;
struct __BSTree {
    BinTree * root;
    size_t size;
};

void BSTree_init(BSTree * self);
void BSTree_deinit(BSTree * self);

size_t BSTree_size     (BSTree * self);

void   BSTree_insert   (BSTree * self, int value);
bool   BSTree_lookup   (BSTree * self, int key);
int BSTree_search   (BSTree * self, int key);
int BSTree_delete   (BSTree * self, int key);
void   BSTree_clear    (BSTree * self);

