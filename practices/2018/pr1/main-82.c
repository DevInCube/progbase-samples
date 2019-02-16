#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

// DynArray module interface
typedef struct __DynArray DynArray;
struct __DynArray
{
    int *array;
    int capacity;
    int length;
};

void DynArray_init(DynArray *self);
void DynArray_deinit(DynArray *self);
void DynArray_add(DynArray *self, int value);
void DynArray_print(const DynArray *self);
//

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
int Queue_size(Queue * self);
void Queue_print(Queue * self);
//

int main()
{
    Stack stack;
    Stack_init(&stack);
    assert(Stack_isEmpty(&stack) == true);
    Stack_push(&stack, 13);
    assert(Stack_isEmpty(&stack) == false);
    assert(Stack_peek(&stack) == 13);
    Stack_push(&stack, 0);
    Stack_push(&stack, -5);
    assert(Stack_peek(&stack) == -5);
    int val = Stack_pop(&stack);
    assert(val == -5);
    Stack_pop(&stack);
    val = Stack_pop(&stack);
    assert(val == 13);
    assert(Stack_isEmpty(&stack) == true);
    Stack_deinit(&stack);

    return 0;
}

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
//

int main0()
{
    DynArray darray;
    DynArray_init(&darray);
    while (1)
    {
        int input = 0;
        scanf("%i", &input);
        if (input > 0)
        {
            DynArray_add(&darray, input);
        }
        else
        {
            break;
        }
    }
    DynArray_print(&darray);
    DynArray_deinit(&darray);
    return 1;
}

// DynArray module implementation

void DynArray_init(DynArray *self)
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

void DynArray_deinit(DynArray *self)
{
    free(self->array);
}

static void DynArray_realloc(DynArray *self, int newCapacity)
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

void DynArray_add(DynArray *self, int value)
{
    self->array[self->length] = value;
    //
    self->length += 1;
    //
    if (self->length == self->capacity)
    {
        // realloc
        int newCapacity = self->capacity * 2;
        DynArray_realloc(self, newCapacity);
    }
}

void DynArray_print(const DynArray *self)
{
    for (int i = 0; i < self->length; i++)
    {
        int value = self->array[i];
        printf("%i, ", value);
    }
    printf("\n");
}
