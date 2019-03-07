// gcc *.c
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

#include "intbintree.h"
#include "bstree.h"

void printBinTree(BinTree * root);
void clearBinTree(BinTree * root);

int main()
{
    int nums[] = {50, 30, 90, 20, 40, 100};
    const int len = sizeof(nums) / sizeof(nums[0]);
    BSTree bst;
    BSTree_init(&bst);
    for (int i = 0; i < len; i++)
    {
        BSTree_insert(&bst, nums[i]);
    }
    for (int i = 0; i < len; i++)
    {
        assert(BSTree_lookup(&bst, nums[i]));
    }
    printBinTree(bst.root);
    // @todo free all
    BSTree_deinit(&bst);
    return 0;
}
static void printValueOnLevel(BinTree * node, char pos, int lvl)
{
    for (int i = 0; i < lvl; i++) { 
        printf("...."); 
    }
    printf("%c: ", pos); 
    if (node == NULL) { 
        printf("(null)\n"); 
    } else { 
        printf("%i\n", node->key); 
    }
}
static void printNode(BinTree * node, char pos, int lvl)
{
    if (node != NULL && (node->left != NULL || node->right != NULL)) 
    {
        printNode(node->right, 'R', lvl + 1);
    }
    printValueOnLevel(node, pos, lvl);
    if (node != NULL && (node->left != NULL || node->right != NULL))
    {
        printNode(node->left, 'L', lvl + 1);
    }
}

void printBinTree(BinTree * root) { printNode(root, '+', 0); }