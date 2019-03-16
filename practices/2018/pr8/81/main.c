// gcc -g main.c -lprogbase -lm
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

#include "bintree.h"
#include "bstree.h"

int main()
{
    BSTree bst;
    BSTree_init(&bst); 

    Student kp81[] =
    {
        {20, "Podlesniuk"},
        {14, "Lialiuk"},
        {7, "Ivahnenko"},
        {15, "Mozgova"},
    };
    int len = sizeof(kp81) / sizeof(kp81[0]);

    for (int i = 0; i < len; i++)
    {
        Student item = kp81[i];
        BSTree_insert(&bst, item);
    }

    assert(BSTree_lookup(&bst, 15) == true);
    assert(BSTree_lookup(&bst, 105) == false);

    assert(BSTree_search(&bst, 100) == NULL);
    Student * f = BSTree_search(&bst, 14);
    assert(strcmp(f->fullname, "Lialiuk") == 0);

    BSTree_print(&bst);
    puts("\n");
    clearTree(bst.root);
    puts("\n---");

    BSTree_deinit(&bst);
    return 0;
}