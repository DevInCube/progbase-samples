#pragma once



//
struct __Queue
{
    char ** items;
    int capacity;
    int first;
    int last;
};
typedef struct __Queue Queue;

void Queue_init(Queue * self);
void Queue_deinit(Queue * self);
void Queue_enqueue(Queue * self, char * value);
char * Queue_dequeue(Queue * self);
int Queue_size(Queue * self);
void Queue_print(Queue * self);
//