#include "list.h"

void List_init(List * self) { self->size = 0; }
void List_add(List * self, void * value) { self->items[self->size++] = value; }
void * List_get(List * self, int index) { return self->items[index]; }
int List_size(List * self) { return self->size; } 