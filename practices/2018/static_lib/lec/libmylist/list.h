#pragma once

typedef struct __List List;
struct __List
{
    void * items[100];
    int size;
};

void List_init(List * self);
void List_add(List * self, void * value);
void * List_get(List * self, int index);
int List_size(List * self);