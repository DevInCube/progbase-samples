#include "intbintree.h"
#include <stdlib.h>

void   BinTree_init     (BinTree * self, int value)
{
    self->value = value;
    self->left = NULL;
    self->right = NULL;
}
void   BinTree_deinit   (BinTree * self) {}

BinTree * BinTree_alloc (int value)
{
    BinTree * self = malloc(sizeof(BinTree));
    BinTree_init(self, value);
    return self;
}
void   BinTree_free     (BinTree * self) { free(self); }