#include <stdlib.h>
#include <stdio.h>

#include "stack.h"

// Stack impl

void Stack_init(Stack * stack) 
{
    stack->cap = 16;
    stack->length = 0;
    stack->arr = malloc(sizeof(int) * stack->cap);
}
void Stack_deinit(Stack * stack) 
{
    free(stack->arr);
}
void Stack_push(Stack * stack, int value)
{
    stack->arr[stack->length] = value;
    stack->length += 1;
    // realloc mem
    if (stack->length == stack->cap)
    {
        int newcap = stack->cap * 2;
        char *newarr = realloc(stack->arr, sizeof(char) * newcap);
        if (newarr == NULL)
        {
            free(stack->arr);
            fprintf(stderr, "Reallocating memory error\n");
            abort();
        }
        printf("Reallocated from %i to %i\n", stack->cap, newcap);
        stack->arr = newarr;
        stack->cap = newcap;
    }
}
int Stack_pop(Stack * stack)
{
    int oldValue = stack->arr[stack->length - 1];
    stack->length -= 1;
    return oldValue;
}

int Stack_peek(Stack * stack)
{
    return stack->arr[stack->length - 1];
}
size_t Stack_size(const Stack * stack) 
{
    return stack->length;
}
void Stack_print(const Stack * stack) 
{
    for (int i = 0; i < stack->length; i++)
    {
        printf("%i, ", stack->arr[i]);
    }
    printf("\n");
}

//