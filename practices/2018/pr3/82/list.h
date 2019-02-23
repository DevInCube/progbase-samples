#pragma once

#include <stdlib.h>
#include <stdbool.h>

typedef void * T;

struct  __List
{
    void ** items;
    size_t capacity;
    size_t size;
};

typedef struct __List List;

void    List_init     (List * self);
void    List_deinit   (List * self);

List *  List_alloc    (void);
void    List_free     (List * self);

T List_get      (List * self, int index);
void    List_set      (List * self, int index, T value);
size_t  List_size     (List * self);
void    List_insert   (List * self, int index, T value);
void    List_removeAt (List * self, int index);

void    List_add      (List * self, T value);
void    List_remove   (List * self, T value);
int     List_indexOf  (List * self, T value);
bool    List_contains (List * self, T value);
bool    List_isEmpty  (List * self);
void    List_clear    (List * self);