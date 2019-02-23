#include <stdio.h>

#include "queue.h"

void Queue_init(Queue * self)
{
    self->first = 0;
    self->last = 0;
}
void Queue_deinit(Queue * self)
{

}

void Queue_enqueue(Queue * self, int value)
{
    self->items[self->last] = value;
    self->last += 1;
    if (self->last == MAX_QUEUE_SIZE)
    {
        self->last = 0;
    }
    if (self->last == self->first) 
    {
        fprintf(stderr, "Queue is full");
        abort();
    }
}
int  Queue_dequeue(Queue * self)
{ 
    int value = self->items[self->first];
    self->first += 1;
    if (self->first == MAX_QUEUE_SIZE) 
    {
        self->first = 0;
    }
    return value;
}
size_t  Queue_size(Queue * self)
{
    if (self->last >= self->first)
        return self->last - self->first;
    return MAX_QUEUE_SIZE - self->first + self->last;
}