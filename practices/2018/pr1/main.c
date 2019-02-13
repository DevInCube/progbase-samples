#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>


struct __DynArray
{
    int cap;
    int length;
    char *arr;
};

typedef struct __DynArray DynArray;

void DynArray_init(DynArray *darray); 
void DynArray_deinit(DynArray *darray);
void DynArray_add(DynArray *darray, char newValue);
void DynArray_print(const DynArray *darray);

struct __Stack 
{
    int cap;
    int length; 
    char *arr;
};
typedef struct __Stack Stack;

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

//   "({]"
//   "({})[]"

int typeEquals(char a, char b)
{
    if (a == '(' && b == ')') return 1;
    if (a == '{' && b == '}') return 1;
    if (a == '[' && b == ']') return 1;
    return 0;
}

int isBalanced(const char * str)
{
    Stack stack;
    Stack_init(&stack);

    const char * p = str;
    while (*p != '\0') 
    {
        if (strchr("([{", *p))
        {
            Stack_push(&stack, *p);
        } 
        else 
        {
            if (typeEquals(Stack_peek(&stack), *p))
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
    int result = 0;
    if (Stack_size(&stack) == 0) 
    {
        result = 1;
    }
    Stack_deinit(&stack);
    return result;
}

int main(int argc, char const *argv[])
{
    assert(isBalanced("({]") == 0);
    assert(isBalanced("({}])") == 0);
    assert(isBalanced("(") == 0);
    assert(isBalanced("({") == 0);
    assert(isBalanced("({}") == 0);
    assert(isBalanced(")()") == 0);
    assert(isBalanced(")()(") == 0);
    assert(isBalanced("({})[]") == 1);
    assert(isBalanced("({[]})") == 1);
    assert(isBalanced("({[]()})") == 1);
    assert(isBalanced("(){}[]") == 1);
    // Stack stack;
    // Stack_init(&stack);

    // Stack_push(&stack, 14);
    // Stack_push(&stack, 12);
    // Stack_push(&stack, 3);
    // Stack_pop(&stack);
    // Stack_push(&stack, 0);
    // Stack_push(&stack, 13);

    // Stack_print(&stack);

    // Stack_deinit(&stack);
    //


    // DynArray daLetters;
    // DynArray daNonLetters;

    // DynArray_init(&daLetters);
    // DynArray_init(&daNonLetters);
    // //
    // char input = '\0';
    // while (1)
    // {
    //     input = getchar();
    //     getchar();
    //     if (isspace(input))
    //     {
    //         break;
    //     }
    //     if (isalpha(input))
    //         DynArray_add(&daLetters, input);
    //     else
    //         DynArray_add(&daNonLetters, input);
        
    // }
    // DynArray_print(&daLetters);
    // DynArray_print(&daNonLetters);

    // DynArray_deinit(&daLetters);
    // DynArray_deinit(&daNonLetters);

    return 0;
}

//---------------------------------------
 
void DynArray_deinit(DynArray *darray)
{
    free(darray->arr);

}

void DynArray_add(DynArray *darray, char newValue)
{
    darray->arr[darray->length] = newValue;
    darray->length += 1;
    // realloc mem
    if (darray->length == darray->cap)
    {
        int newcap = darray->cap * 2;
        char *newarr = realloc(darray->arr, sizeof(char) * newcap);
        if (newarr == NULL)
        {
            free(darray->arr);
            fprintf(stderr, "Reallocating memory error\n");
            abort();
        }
        printf("Reallocated from %i to %i\n", darray->cap, newcap);
        darray->arr = newarr;
        darray->cap = newcap;
    }
}

void DynArray_print(const DynArray *darray)
{
    for (int i = 0; i < darray->length; i++)
    {
        printf("%c,", darray->arr[i]);
    }
    printf("\n");
}

void DynArray_init(DynArray *darray)
{ 
    darray->cap = 4;
    darray->arr = malloc(sizeof(char) * darray->cap);
    if (darray == NULL) 
    {
        fprintf(stderr, "Allocating memory error\n");
        abort();
    }
    darray->length = 0;
}
