// gcc *.c
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#include "intbintree.h"

void printBinTree(BinTree * root);
void clearBinTree(BinTree * root);

int main()
{
    BinTree * root = BinTree_alloc(50);
    BinTree * rootLeft = root->left = BinTree_alloc(30);
    BinTree * rootRight = root->right = BinTree_alloc(90);
    rootLeft->left = BinTree_alloc(20);
    rootLeft->right = BinTree_alloc(40);
    rootRight->right = BinTree_alloc(100);
    printBinTree(root);
    // @todo free all
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
        printf("%i\n", node->value); 
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