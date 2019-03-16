#include "bintree.h"

#include <stdlib.h>

void   BinTree_init     (BinTree * self, Student value)
{
    self->key = Student_key(value); 
    self->value = value;
    self->left = NULL; 
    self->right = NULL;
} 
void   BinTree_deinit   (BinTree * self)
{

}

BinTree * BinTree_alloc (Student value) 
{
    BinTree * self = malloc(sizeof(BinTree));
    BinTree_init(self, value); 
    return self;
}
void   BinTree_free     (BinTree * self)
{
    BinTree_deinit(self);
    free(self); 
}