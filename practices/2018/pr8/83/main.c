// gcc *.c
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

typedef struct __Student Student;
struct __Student
{
    int id;
    char fullname[100];
};

typedef struct __BinTree BinTree;
struct __BinTree
{
    int key;
    Student value;  // set on init/alloc
    BinTree *left;  // set to NULL on init
    BinTree *right; // set to NULL on init
};

BinTree *BinTree_alloc(Student value);
void BinTree_free(BinTree *self);

//
typedef struct __BSTree BSTree;
struct __BSTree
{
    BinTree *root;
};

void BSTree_init(BSTree *self);

void traverseInOrder(BinTree *node);

void clearBinTree(BinTree *node);

void BSTree_insert(BSTree *self, Student value);
bool BSTree_lookup(BSTree *self, int key);
Student *BSTree_search(BSTree *self, int key);

Student BSTree_delete(BSTree *self, int key);

void BSTree_print(BSTree *self);

int main()
{
    BSTree bstree;
    BSTree_init(&bstree);
    //
    //int nums[] = {46, -40, -10, -31, -46, 18};
    //const int numsLen = sizeof(nums) / sizeof(nums[0]);
    Student sts[] = {
        {2, "Boychuk"},
        {45, "Matiiuk"},
        {3, "Betin"},
        {1, "Koval"},
    };
    const int stsLen = sizeof(sts) / sizeof(sts[0]);

    for (int i = 0; i < stsLen; i++)
    {
        Student value = sts[i];
        BSTree_insert(&bstree, value);
    }

    for (int i = 0; i < stsLen; i++)
    {
        Student value = sts[i];
        int key = value.id;
        assert(BSTree_lookup(&bstree, key) == true);
    }

    assert(BSTree_lookup(&bstree, -13) == false);

    Student *pst = BSTree_search(&bstree, 45);
    if (pst == NULL)
        printf("Not found\n");
    else
        printf("%i: %s\n", 45, pst->fullname);

    // root = BinTree_alloc(46);
    // root->left = BinTree_alloc(-40);
    // root->left->right = BinTree_alloc(-10);
    // root->left->right->left = BinTree_alloc(-31);
    // root->left->left = BinTree_alloc(-46);
    // root->left->right->right = BinTree_alloc(18);
    //
    BSTree_print(&bstree);
    puts("\n");
    BSTree_delete(&bstree, 2);
    BSTree_print(&bstree);
    puts("\n");
    traverseInOrder(bstree.root);
    puts("\n");
    // traversePreOrder(root); puts("\n");
    // traversePostOrder(root); puts("\n");
    clearBinTree(bstree.root);
    return 0;
}

typedef BinTree *BinTreeLink;

BinTree *BinTreeLink_child(BinTreeLink *self) { return *self; }
void BinTreeLink_setChild(BinTreeLink *self, BinTree *child) { *self = child; }
// preprocessor macros
#define BinTreeLink_create(NODEPTR) &(NODEPTR)

static BinTreeLink *findMostLeftMissingNodeParentLink(BinTreeLink *parentToChildLink)
{
    BinTree *childNode = BinTreeLink_child(parentToChildLink);
    if (childNode->left == NULL)
        return parentToChildLink;
    BinTreeLink *leftChildLink = BinTreeLink_create(childNode->left);
    return findMostLeftMissingNodeParentLink(leftChildLink);
}

static void modifyTreeOnDelete(BinTreeLink *parentToChildLink, BinTree *node)
{
    BinTree *replacementNode = NULL; // to place this on node's position
    if (node->left == NULL && node->right == NULL)
    {
        // case A: no children
        // replacementNode = NULL;
    }
    else if (node->left == NULL || node->right == NULL)
    {
        // case B: one child
        BinTree *child = node->left != NULL
            ? node->left
            : node->right;
        //
        replacementNode = child;
    }
    else
    {
        // case C: two children
        BinTreeLink *rightChildLink = BinTreeLink_create(node->right);
        BinTreeLink *mostLeftMissingNodeParentLink = findMostLeftMissingNodeParentLink(rightChildLink);
        BinTree *mostLeftParent = BinTreeLink_child(mostLeftMissingNodeParentLink);
        // move most left parent's right child to parent's position
        BinTreeLink_setChild(mostLeftMissingNodeParentLink, mostLeftParent->right);
        // move most left parent to node's position
        mostLeftParent->left = node->left;
        mostLeftParent->right = node->right;
        //
        replacementNode = mostLeftParent;
    }
    BinTreeLink_setChild(parentToChildLink, replacementNode);
}

static Student deleteNode(BinTreeLink *parentToChildLink, BinTree * node)
{
    Student nodeValue = node->value; // temporary value copy
    modifyTreeOnDelete(parentToChildLink, node);
    BinTree_free(node);  // release allocated memory
    return nodeValue;  // return value of removed node
}

static Student deleteKey(BinTreeLink *parentToChildLink, int key)
{
    BinTree *node = *parentToChildLink;
    if (node == NULL)
    {
        fprintf(stderr, "No value with such key `%i`\n", key);
        abort();
    }
    if (key == node->key)
        return deleteNode(parentToChildLink, node);
    if (key < node->key)
        return deleteKey(BinTreeLink_create(node->left), key);
    if (key > node->key)
        return deleteKey(BinTreeLink_create(node->right), key);
}

Student BSTree_delete(BSTree *self, int key)
{
    deleteKey(BinTreeLink_create(self->root), key);
}

static bool lookupBinTree(BinTree *node, int key)
{
    if (node == NULL)
        return false;
    if (node->key == key)
        return true;
    if (key < node->key)
        return lookupBinTree(node->left, key);
    if (key > node->key)
        return lookupBinTree(node->right, key);
}

bool BSTree_lookup(BSTree *self, int key)
{
    return lookupBinTree(self->root, key);
    // ALT: return BSTree_search(self, key) != NULL;
}

static Student *searchBinTree(BinTree *node, int key)
{
    if (node == NULL)
        return NULL;
    if (node->key == key)
        return &node->value;
    if (key < node->key)
        return searchBinTree(node->left, key);
    if (key > node->key)
        return searchBinTree(node->right, key);
}

Student *BSTree_search(BSTree *self, int key)
{
    return searchBinTree(self->root, key);
}

void BSTree_init(BSTree *self)
{
    self->root = NULL;
}

static void printValueOnDepth(BinTree *node, char pos, int depth)
{
    for (int i = 0; i < depth; i++)
    {
        printf("....");
    }
    printf("%c: ", pos);

    if (node == NULL)
    {
        printf("(null)\n");
    }
    else
    {
        printf("id: %i, fullname: %s\n", node->value.id, node->value.fullname);
    }
}

static void printNode(BinTree *node, char pos, int d)
{
    bool hasChild = node != NULL && (node->left != NULL || node->right != NULL);
    if (hasChild)
        printNode(node->right, 'R', d + 1);
    printValueOnDepth(node, pos, d);
    if (hasChild)
        printNode(node->left, 'L', d + 1);
}

void BSTree_print(BSTree *self)
{
    printNode(self->root, '+', 0);
}

static int getStudentKey(Student *pst)
{
    return pst->id;
}

static void insertBinTree(BinTree *node, BinTree *newNode)
{
    assert(node != NULL);
    if (newNode->key == node->key)
    {
        fprintf(stderr, "Key `%i` already exists in BST\n", newNode->key);
        abort();
    }
    else if (newNode->key < node->key)
    {
        if (node->left == NULL)
            node->left = newNode;
        else
            insertBinTree(node->left, newNode);
    }
    else
    {
        if (node->right == NULL)
            node->right = newNode;
        else
            insertBinTree(node->right, newNode);
    }
}

void BSTree_insert(BSTree *self, Student value)
{
    BinTree *newNode = BinTree_alloc(value);
    if (self->root == NULL)
    {
        self->root = newNode;
        return;
    }
    //
    insertBinTree(self->root, newNode);
}

BinTree *BinTree_alloc(Student value)
{
    BinTree *self = malloc(sizeof(BinTree));
    self->value = value;
    self->key = getStudentKey(&value);
    self->left = NULL;
    self->right = NULL;
    return self;
}

void BinTree_free(BinTree *self) { free(self); }

void traverseInOrder(BinTree *node)
{
    if (node == NULL)
        return;

    traverseInOrder(node->left);  // left
    printf("%i, ", node->key);    // current
    traverseInOrder(node->right); // right
}

void clearBinTree(BinTree *node)
{
    if (node == NULL)
        return;

    if (node->left)
        clearBinTree(node->left);
    if (node->right)
        clearBinTree(node->right);
    BinTree_free(node);
}