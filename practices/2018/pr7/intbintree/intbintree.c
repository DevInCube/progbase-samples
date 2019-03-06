#include "intbintree.h"
#include <stdlib.h>

void   BinTree_init     (BinTree * self, int key /*, TVal value*/)
{
    self->key = key;
    self->left = NULL;
    self->right = NULL;
}
void   BinTree_deinit   (BinTree * self) {}

BinTree * BinTree_alloc (int key /*, TVal value*/)
{
    BinTree * self = malloc(sizeof(BinTree));
    BinTree_init(self, key);
    return self;
}
void   BinTree_free     (BinTree * self) { free(self); }