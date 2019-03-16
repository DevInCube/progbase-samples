#include <stdio.h>
#include "bstree.h"

void traverseInOrder(BinTree * node)
{
    if (node == NULL) return;

    traverseInOrder(node->left);
    printf("[%i]`%s`, ", node->key, node->value.fullname);
    traverseInOrder(node->right);
}

void traversePreOrder(BinTree * node);
void traversePostOrder(BinTree * node);

void clearTree(BinTree * node)
{
    if (node == NULL) return;
    clearTree(node->left);
    clearTree(node->right);
    BinTree_free(node);
}



void BSTree_init(BSTree *self)
{
    self->root = NULL; 
}

void BSTree_deinit(BSTree *self)
{
    
}

static void insert(BinTree * node, BinTree * newNode)
{
    if (node->key == newNode->key)
    {
        fprintf(stderr, "Not unique\n");
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
    else  // newNode->value > node->value
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



void BSTree_insert(BSTree * self, Student value)
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

static void printValueOnDepth(BinTree * node, char pos, int depth)
{
   for (int i = 0; i < depth; i++) {
       printf("....");
   }
   printf("%c: ", pos); 

   if (node == NULL) {
       printf("(null)\n");
   } else {
       printf("[%i] `%s`\n", node->key, node->value.fullname);
   }
}

static void printNode(BinTree * node, char pos, int depth)
{
    bool hasChild = node != NULL && (node->left != NULL || node->right != NULL);
    if (hasChild) printNode(node->right, 'R', depth + 1);
    printValueOnDepth(node, pos, depth);
    if (hasChild) printNode(node->left, 'L', depth + 1);
}

void BSTree_print(BSTree * self)
{
    printNode(self->root, '+', 0);
}

static bool lookup(BinTree * node, int key)
{
    if (node == NULL) return false;
    if (node->key == key) return true;
    if (key < node->key) return lookup(node->left, key);
    if (key > node->key) return lookup(node->right, key);
} 

bool BSTree_lookup(BSTree * self, int key)
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

Student * BSTree_search(BSTree * self, int key)
{
    return search(self->root, key); 
}

static BinTree * minNode(BinTree * node)
{
    if (node == NULL) return NULL;
    if (node->left == NULL) return node;
    return minNode(node->left); 
}

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
        BinTree * child = (node->left != NULL) 
            ? node->left
            : node->right; 
        if (parent->left == node) parent->left = child;
        else parent->right = child;
    }
    else 
    {
        // case C
        BinTree * min = minNode(node->right);
        if (min != NULL)
        {
            int minKey = min->key;
            delete(node->right, minKey, node);
        }
        min->left = node->left;
        min->right = node->right;
        //
        if (parent->left == node) parent->left = min;
        else parent->right = min;
    }
}

static void delete(BinTree * node, int key, BinTree * parent)
{
    if (node == NULL)
    {
        fprintf(stderr, "Key `%i` not found", key);
        abort();
    }
    if (node->key == key)
    {   
        modifyTreeOnDelete(node, parent);
        BinTree_free(node);
    }
    else if (key < node->key)
    {
        delete(node->left, key, node);
    }
    else
    {
        delete(node->right, key, node);
    }
    
}

Student * BSTree_delete(BSTree * self, int key)
{
    return NULL; // @todo
}