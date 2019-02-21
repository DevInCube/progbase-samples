#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "stack.h"


// Stack module implementation
void Stack_init(Stack *self)
{
    self->length = 0;
    self->capacity = 4;
    self->array = malloc(sizeof(int) * self->capacity);
    if (self->array == NULL)
    {
        fprintf(stderr, "Allocation error");
        abort();
    }
}
void Stack_deinit(Stack *self)
{
    free(self->array);
}

static void Stack_realloc(Stack *self, int newCapacity)
{
    int *newArray = realloc(self->array, sizeof(int) * newCapacity);
    if (newArray == NULL)
    {
        free(self->array);
        fprintf(stderr, "Reallocation error");
        abort();
    }
    self->array = newArray;
    self->capacity = newCapacity;
    printf("Reallocated");
}

void Stack_push(Stack *self, int value)
{
    self->array[self->length] = value;
    //
    self->length += 1;
    //
    if (self->length == self->capacity)
    {
        // realloc
        int newCapacity = self->capacity * 2;
        Stack_realloc(self, newCapacity);
    }
}
int Stack_pop(Stack *self)
{
    if (self->length == 0) 
    {
        fprintf(stderr, "Stack underflow");
        abort();
    }
    int val = self->array[self->length - 1];
    self->length -= 1;
    return val;
}
int Stack_peek(Stack *self)
{
    if (self->length == 0) 
    {
        fprintf(stderr, "Stack underflow");
        abort();
    }
    int val = self->array[self->length - 1];
    return val;
}
bool Stack_isEmpty(Stack *self)
{
    return self->length == 0;
}