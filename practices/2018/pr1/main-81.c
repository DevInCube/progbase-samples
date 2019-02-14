#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

struct __DynArray
{
    int capacity;
    int *items;
    int length;
};
typedef struct __DynArray DynArray;

struct __Stack
{
    int capacity;
    int *items;
    int length;
};
typedef struct __Stack Stack;

void reallocArray(DynArray *p, int newCapacity)
{
    int *newArr = realloc(p->items, sizeof(int) * newCapacity);
    if (newArr == NULL)
    {
        free(p->items);
        fprintf(stderr, "Error: Not reallocated");
        abort();
    }
    p->items = newArr;
    p->capacity = newCapacity;
}

void Stack_init(Stack *p)
{
    p->capacity = 4;
    p->items = malloc(sizeof(int) * p->capacity);
    p->length = 0;
    if (p->items == NULL)
    {
        fprintf(stderr, "Error: Not allocated");
        abort();
    }
}

void DynArray_init(DynArray *p)
{
    p->capacity = 4;
    p->items = malloc(sizeof(int) * p->capacity);
    p->length = 0;
    if (p->items == NULL)
    {
        fprintf(stderr, "Error: Not allocated");
        abort();
    }
}

void add(DynArray *p, int value)
{
    p->items[p->length] = value;
    p->length += 1;
    //
    if (p->length == p->capacity)
    {
        printf("Not enough memory. Reallocating...\n");
        int newCapacity = p->capacity * 2;
        reallocArray(p, newCapacity);
    }
}

void Stack_reallocArray(Stack *p, int newCapacity)
{
    int *newArr = realloc(p->items, sizeof(int) * newCapacity);
    if (newArr == NULL)
    {
        free(p->items);
        fprintf(stderr, "Error: Not reallocated");
        abort();
    }
    p->items = newArr;
    p->capacity = newCapacity;
}

void Stack_push(Stack *p, int value)
{
    p->items[p->length] = value;
    p->length += 1;
    //
    if (p->length == p->capacity)
    {
        printf("Not enough memory. Reallocating...\n");
        int newCapacity = p->capacity * 2;
        Stack_reallocArray(p, newCapacity);
    }
}

void print(const DynArray *p)
{
    for (int i = 0; i < p->length; i++)
    {
        printf("%i,", p->items[i]);
    }
    printf("\n");
}

void deinit(DynArray *p)
{
    free(p->items);
}

int Stack_pop(Stack *p)
{
    int top = p->items[p->length - 1];
    p->length -= 1;
    return top;
}

int Stack_peek(Stack *p)
{
    return p->items[p->length - 1];
}

int Stack_isEmpty(Stack *p)
{
    return p->length == 0;
}

void Stack_deinit(Stack *p)
{
    free(p->items);
}

int typeEquals(int open, int close)
{
    if (open == '(' && close == ')') return 1;
    if (open == '{' && close == '}') return 1;
    if (open == '[' && close == ']') return 1;
    return 0;
}

int isBalanced(const char *str)
{
    Stack stack;
    Stack_init(&stack);

    const char *p = str;
    while (*p != '\0')
    {
        if (strchr("({[", *p))
        {
            Stack_push(&stack, *p);
        }
        else
        {
            if (Stack_isEmpty(&stack))
            {
                Stack_deinit(&stack);
                return 0;
            }
            int top = Stack_peek(&stack);
            if (typeEquals(top, *p))
            {
                Stack_pop(&stack);
            }
            else
            {
                Stack_deinit(&stack);
                return 0;
            }
        }
        p += 1;
    }
    if (Stack_isEmpty(&stack))
    {
        Stack_deinit(&stack);
        return 1;
    }
    else
    {
        Stack_deinit(&stack);
        return 0;
    }
}

int main()
{
    assert(isBalanced("[(])") == 0);
    assert(isBalanced("()(") == 0);
    assert(isBalanced("(") == 0);
    assert(isBalanced(")(") == 0);
    assert(isBalanced("()") == 1);
    assert(isBalanced("{}") == 1);
    assert(isBalanced("[]") == 1);
    assert(isBalanced("[()]") == 1);
    assert(isBalanced("[(){}]") == 1);
    assert(isBalanced("[[]]") == 1);

    Stack stack;
    Stack_init(&stack);

    Stack_push(&stack, 43);
    Stack_push(&stack, -10);
    Stack_push(&stack, 5);
    assert(Stack_pop(&stack) == 5);
    assert(Stack_pop(&stack) == -10);
    assert(Stack_isEmpty(&stack) == 0);
    assert(Stack_peek(&stack) == 43);
    assert(Stack_isEmpty(&stack) == 0);
    assert(Stack_pop(&stack) == 43);
    assert(Stack_isEmpty(&stack) == 1);

    Stack_deinit(&stack);

    return 0;

    DynArray array = {0};
    DynArray_init(&array);
    int input = 0;
    do
    {
        scanf("%i", &input);
        if (input > 0)
        {
            add(&array, input);
        }
    } while (input > 0);
    print(&array);
    deinit(&array);
    return 0;
}
