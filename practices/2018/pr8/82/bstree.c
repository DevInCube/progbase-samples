#include "bstree.h"
#include <stdio.h>

void BSTree_init(BSTree * self)
{
    self->root = NULL; 
}
void BSTree_deinit(BSTree * self)
{

}

static void insert(BinTree * node, BinTree * newNode)
{
    if (newNode->key == node->key)
    {
        fprintf(stderr, "`%i` Already exists\n", newNode->key);
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
            insert(node->left, newNode); 
        }
    } 
    else if (newNode->key > node->key)
    {
        if (node->right == NULL)
        {
            node->right = newNode; 
        }
        else 
        {
            insert(node->right, newNode); 
        }
    }
}

void   BSTree_insert   (BSTree * self, Student value)
{
    BinTree * newNode = BinTree_alloc(value);
    if (self->root == NULL)
    {
        self->root = newNode;
    }
    else 
    {
        insert(self->root, newNode);
    }
}

static bool lookup(BinTree * node, int key) 
{
    if (node == NULL) return false;
    if (node->key == key) return true;
    if (key < node->key) return lookup(node->left, key);
    if (key > node->key) return lookup(node->right, key);
}
 
bool   BSTree_lookup   (BSTree * self, int key)
{
    return lookup(self->root, key);
}

static Student * search(BinTree * node, int key) 
{
    if (node == NULL) return NULL; 
    if (node->key == key) return &node->value;
    if (key < node->key) return search(node->left, key);
    if (key > node->key) return search(node->right, key);
}
  
Student *   BSTree_search   (BSTree * self, int key)
{
    return search(self->root, key);
}

static BinTree * searchMin(BinTree * node)
{
    if (node == NULL) return NULL; 
    if (node->left == NULL) return node;
    return searchMin(node->left); 
}

static Student delete(BinTree * node, int key, BinTree * parent);

static void modifyTreeOnDelete(BinTree * node, BinTree * parent)
{
    if (node->left == NULL && node->right == NULL)
    { 
        // case A
        if (parent->left == node) parent->left = NULL;
        else parent->right = NULL;
    }
    else if (node->left == NULL || node->right == NULL)
    {
        // case B
        BinTree * child = (node->left != NULL) ? node->left : node->right;
        if (parent->left == node) parent->left = child;
        else parent->right = child;
    }
    else 
    {
        // case C 
        BinTree * minNode = searchMin(node->right);
        int minKey = minNode->key;
        Student deletedValue = delete(node->right, minKey, parent);
        BinTree * newMin = BinTree_alloc(deletedValue);
        newMin->left = node->left;
        newMin->right = node->right;
        if (parent->left == node) parent->left = minNode;
        else parent->right = minNode;
        
    }
}

static Student delete(BinTree * node, int key, BinTree * parent)
{
    if (node == NULL) 
    {
        fprintf(stderr, "`%i` not found\n", key);
        abort();
    }
    if (key < node->key) return delete(node->left, key, node);
    else if (key > node->key) return delete(node->right, key, node);
    else {
        modifyTreeOnDelete(node, parent);
        Student old = node->value;
        BinTree_free(node);  
        return old;
    }
}

Student BSTree_delete   (BSTree * self, int key)
{
    BinTree fakeRoot;
    fakeRoot.left = self->root;
    Student old = delete(self->root, key, &fakeRoot);
    self->root = fakeRoot.left;
    return old;
}