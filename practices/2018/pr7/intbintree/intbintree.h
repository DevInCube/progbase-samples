#pragma once

typedef struct __BinTree BinTree;
struct __BinTree 
{
   int value;
   BinTree * left;
   BinTree * right;
};

void   BinTree_init     (BinTree * self, int value);
void   BinTree_deinit   (BinTree * self);

BinTree * BinTree_alloc (int value);
void   BinTree_free     (BinTree * self);
