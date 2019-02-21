#pragma once

#include <stdlib.h>

// Queue interface
typedef struct __Queue Queue;
struct __Queue
{
    int array[10];
};
void Queue_init(Queue *self);
void Queue_deinit(Queue *self);
void Queue_enqueue(Queue *self, int value);
int Queue_dequeue(Queue *self);
size_t Queue_size(Queue * self);
void Queue_print(Queue * self);
//