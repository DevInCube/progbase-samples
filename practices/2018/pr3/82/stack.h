#pragma once

// Stack module interface
typedef struct __Stack Stack;
struct __Stack
{
    int *array;
    int capacity;
    int length;
};
void Stack_init(Stack *self);
void Stack_deinit(Stack *self);
void Stack_push(Stack *self, int value);
int Stack_pop(Stack *self);
int Stack_peek(Stack *self);
bool Stack_isEmpty(Stack *self);
//