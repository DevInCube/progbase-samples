#pragma once

#include <stdlib.h>

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
size_t  Queue_size(Queue * self);