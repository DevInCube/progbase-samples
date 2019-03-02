#pragma once
#include <stdlib.h>
#include <stdbool.h>

struct __List 
{
    void ** items;
    size_t size;
    size_t capacity;
};
typedef struct __List List;

List *  List_alloc    (void);
void    List_free     (List * self);
void List_init(List * self);
void List_deinit(List * self);

void *  List_get      (List * self, int index); 
void    List_set      (List * self, int index, void * value);
size_t  List_size     (List * self);
void    List_insert   (List * self, int index, void * value);
void    List_removeAt (List * self, int index);

void    List_add      (List * self, void * value);
void    List_remove   (List * self, void * value);
int     List_indexOf  (List * self, void * value);
bool    List_contains (List * self, void * value);
bool    List_isEmpty  (List * self);
void    List_clear    (List * self);