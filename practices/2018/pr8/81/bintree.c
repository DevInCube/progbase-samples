#include "bintree.h"
#include <stdlib.h>

int Student_key(Student st)
{
    return st.id; 
}

BinTree * BinTree_alloc (Student value)
{
    BinTree * self = malloc(sizeof(BinTree));
    self->left = NULL;
    self->right = NULL;
    self->key = Student_key(value); 
    self->value = value;
    return self;
} 
void   BinTree_free     (BinTree * self)
{ 
    free(self);
}