#include <stdlib.h>
#include <stdio.h>

#include "queue.h"
//

void Queue_init(Queue * self)
{
    self->capacity = 16;
    self->first = 0;
    self->last = 0; 
    self->items = malloc(sizeof(char *) * self->capacity);
}

void Queue_deinit(Queue * self)
{
    free(self->items); 
}

void Queue_enqueue(Queue * self, char * value)
{
    self->items[self->last] = value;
    self->last += 1; 
    if (self->last == self->capacity)
    {
        self->last = 0;
    }
    if (self->last == self->first)
    {
        fprintf(stderr, "Queue is full");
    }
}

char * Queue_dequeue(Queue * self) 
{
    char * value = self->items[self->first];
    self->first += 1;
    if (self->first == self->capacity)
    {
        self->first = 0;
    }
    return value;
}

int Queue_size(Queue * self)
{
    if (self->last >= self->first)
        return self->last - self->first; 
    return self->capacity - self->first + self->last; 
}

void Queue_print(Queue * self)
{
    const int length = Queue_size(self);
    printf("Queue %i:\n", length);
    for (int i = self->first; i < self->last; i++) 
    {
        printf("\"%s\"\n", self->items[i]);
    }
}

//