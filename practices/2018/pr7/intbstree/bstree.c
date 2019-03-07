#include "bstree.h"
#include <stdio.h>

size_t BSTree_size(BSTree *self) { return self->size; }

void BSTree_init(BSTree *self)
{
    self->root = NULL;
    self->size = 0;
}
void BSTree_deinit(BSTree *self) {}


static void insertNode(BinTree *node, BinTree * newNode);

void BSTree_insert(BSTree *self, int value)
{
    self->size += 1; // we add or abort, increase size
    int key = value; // getKey(value) for other value types
    BinTree * newNode = BinTree_alloc(key/*, value*/);
    if (self->root == NULL)
    { // if tree is empty - create root
        self->root = newNode;
    }
    else
    { 
        insertNode(self->root, newNode); // enter recursion
    }
}

static void insertNode(BinTree *node, BinTree * newNode)
{
    if (newNode->key == node->key)
    {
        fprintf(stderr, "Key %i already exists\n", newNode->key);
        abort();
    }
    if (newNode->key < node->key)
    {
        if (node->left == NULL)
        {
            node->left = newNode;
        }
        else
        {
            insertNode(node->left, newNode);
        }
    }
    else
    { // newNode->key > node->key
        if (node->right == NULL)
        {
            node->right = newNode;
        }
        else
        {
            insertNode(node->right, newNode);
        }
    }
}

static bool lookupKey(BinTree *self, int key)
{
    if (self == NULL) return false; 
    if (key < self->key) return lookupKey(self->left, key);
    else if (key > self->key) return lookupKey(self->right, key);
    return true; // key == self->key
}

bool BSTree_lookup(BSTree *self, int key)
{
    return lookupKey(self->root, key);
}
int BSTree_search(BSTree *self, int key)
{
    return key;
}
int BSTree_delete(BSTree *self, int key)
{
    return key;
}
void BSTree_clear(BSTree *self)
{
    // @todo free
    self->size = 0;
}