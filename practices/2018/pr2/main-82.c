#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

enum { MAX_QUEUE_SIZE = 10 };

//#define MAX_QUEUE_SIZE 10
struct __Queue
{
    int items[MAX_QUEUE_SIZE];
    int first;
    int last;
};
typedef struct __Queue Queue;

void Queue_init(Queue * self);
void Queue_deinit(Queue * self);

void Queue_enqueue(Queue * self, int value);
int  Queue_dequeue(Queue * self);
int  Queue_size(Queue * self);

int main(int argc, char const *argv[])
{
    Queue q1;
    Queue_init(&q1);

    assert(Queue_size(&q1) == 0);

    Queue_enqueue(&q1, 13);
    assert(Queue_size(&q1) == 1);

    Queue_enqueue(&q1, -42);
    assert(Queue_size(&q1) == 2);
    assert(Queue_dequeue(&q1) == 13);
    assert(Queue_size(&q1) == 1);
    assert(Queue_dequeue(&q1) == -42);

    for (int i = 0; i < MAX_QUEUE_SIZE; i++) 
    {
        Queue_enqueue(&q1, i);
        //assert(Queue_size(&q1) == 1);
        //assert(Queue_dequeue(&q1) == i);
       // assert(Queue_size(&q1) == 0);
    }

    Queue_deinit(&q1);
    return 0;
}

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
int  Queue_size(Queue * self)
{
    if (self->last >= self->first)
        return self->last - self->first;
    return MAX_QUEUE_SIZE - self->first + self->last;
}