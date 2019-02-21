#pragma once

#include <stdlib.h>

// Stack interface
struct __Stack 
{
    int cap;
    int length; 
    char *arr;
};
typedef struct __Stack Stack;

void Stack_init(Stack * stack);
void Stack_deinit(Stack * stack);
void Stack_push(Stack * stack, int value);
int Stack_pop(Stack * stack);
int Stack_peek(Stack * stack);
size_t Stack_size(const Stack * stack);
void Stack_print(const Stack * stack);
//