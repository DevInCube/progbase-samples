#include <stdlib.h>
#include <stdio.h>

/* List interface */

typedef struct List List;

List * List_new(int size);
void List_free(List ** selfPtr);
int List_size(List * self); // sizeof(arr) / sizeof(arr[0])
int List_get(List * self, int i);  // int x = arr[i]
void List_set(List * self, int i, int value);  // arr[i] = value;
void List_addLast(List * self, int value); // arr[size++] = value;
void List_insert(List * self, int index, int value);
void List_remove(List * self, int index); // 

/* Sample Linked List interface */

typedef struct LinkedList LinkedList;
typedef struct Human Human;

LinkedList * LinkedList_new(Human * value);
void LinkedList_free(LinkedList ** selfPtr);

Human * LinkedList_getValue(LinkedList * self);
LinkedList * LinkedList_getNext(LinkedList * self);

int LinkedList_count(LinkedList * self);
void LinkedList_addFirst(LinkedList * self, LinkedList * value);
void LinkedList_addLast(LinkedList * self, LinkedList * value);
void LinkedList_insert(LinkedList * self, int index, LinkedList * value);
void LinkedList_removeFirst(LinkedList * self);
void LinkedList_removeLast(LinkedList * self);
void LinkedList_remove(LinkedList * self, int index);

/* list.c */

struct LinkedList {
    struct ListNode * next;
    Human * data;
};

struct Human {
    int age;
    float weight;
    char name[1000];
};


int main(void) {
    
    // int size = 0;
    // int arr[3] = {4, 5, 6};

    return 0;
}
