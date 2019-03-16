// gcc -g main.c -lprogbase -lm
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#include <assert.h>

#include "bintree.h"

void traverseInOrder(BinTree * node)
{
    if (node == NULL) return;
    traverseInOrder(node->left);
    printf("%i, ", node->key);
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

static void printValueOnLevel(BinTree * node, char pos, int depth)
{
   for (int i = 0; i < depth; i++) {
       printf("....");
   }
   printf("%c: ", pos);

   if (node == NULL) {
       printf("(null)\n");
   } else {
       printf("[%i]`%s`\n", node->key, node->value.fullname);
   }
}

void print(BinTree * node, char pos, int depth)
{
    bool isNotNull = (node != NULL) && (node->left != NULL || node->right != NULL);
    if (isNotNull) print(node->right, 'R', depth + 1);
    printValueOnLevel(node, pos, depth);
    if (isNotNull) print(node->left, 'L', depth + 1);
}

void printTree(BinTree * root)
{
    print(root, '+', 0);
}

#include "bstree.h"

int main()
{
    BSTree bst;
    BSTree_init(&bst); 
 
    Student kp82[] = {
        {13, "Kulinych"},
        {17, "Monko"},
        {14, "Lahman"},
        {16, "Mohulevska"},
        {21, "Syhodolsky"},
        {8, "Zhyrov"},
    };
    int len = sizeof(kp82) / sizeof(kp82[0]);

    for (int i = 0; i < len; i ++)
    {
        Student value = kp82[i];
        BSTree_insert(&bst, value);
    }

    assert(BSTree_lookup(&bst, 14) == true);
    assert(BSTree_lookup(&bst, 104) == false);

    assert(BSTree_search(&bst, 104) == NULL);
    Student * f = BSTree_search(&bst, 14);
    assert(f != NULL);
    assert(strcmp(f->fullname, "Lahman") == 0);

    printTree(bst.root);
    puts("");

    BSTree_delete(&bst, 13);
    assert(BSTree_lookup(&bst, 13) == false);

    printTree(bst.root);
    clearTree(bst.root);

    BSTree_deinit(&bst);
    return 0;
}