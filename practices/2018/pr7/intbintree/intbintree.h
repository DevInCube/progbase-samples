#pragma once

typedef struct __BinTree BinTree;
struct __BinTree 
{
   int key;
   // TVal value;
   BinTree * left;
   BinTree * right;
};

void   BinTree_init     (BinTree * self, int key /*, TVal value*/);
void   BinTree_deinit   (BinTree * self);

BinTree * BinTree_alloc (int key /*, TVal value*/);
void   BinTree_free     (BinTree * self);
