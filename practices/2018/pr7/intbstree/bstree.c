#include "bstree.h"
#include <stdio.h>

size_t BSTree_size(BSTree *self) { return self->size; }

void BSTree_init(BSTree *self)
{
    self->root = NULL;
    self->size = 0;
}
void BSTree_deinit(BSTree *self) {}

static void insertNode(BinTree *node, int key, int value)
{
    if (key == node->key)
    {
        fprintf(stderr, "Key %i already exists\n", key);
        abort();
    }
    if (key < node->key)
    {
        if (node->left == NULL)
        {
            node->left = BinTree_alloc(key); // + value
        }
        else
        {
            insertNode(node->left, key, value);
        }
    }
    else
    { // key > node->key
        if (node->right == NULL)
        {
            node->right = BinTree_alloc(key); // + value
        }
        else
        {
            insertNode(node->right, key, value);
        }
    }
}
static void insertNode(BinTree *node, int key, int value);

void BSTree_insert(BSTree *self, int value)
{
    self->size += 1; // we add or abort, increase size
    int key = value; // getKey(value) for other value types
    if (self->root == NULL)
    { // if tree is empty - create root
        self->root = BinTree_alloc(key/*, value*/);
    }
    else
    {
        insertNode(self->root, key, value); // enter recursion
    }
}
bool BSTree_lookup(BSTree *self, int key)
{
    return false;
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