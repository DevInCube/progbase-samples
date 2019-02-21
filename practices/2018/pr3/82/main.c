#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "stack.h" 

bool brTypeEquals(int opCode, int clCode)
{
    if (opCode == '(' && clCode == ')') return true;
    if (opCode == '[' && clCode == ']') return true;
    if (opCode == '<' && clCode == '>') return true;
    if (opCode == '{' && clCode == '}') return true;
    return false;
}

bool isBalanced(const char * str) 
{
    Stack s;
    Stack_init(&s);

    const char * ch = str;
    while (*ch != '\0')
    {
        if (strchr(")}]>", *ch))
        {
            if (Stack_isEmpty(&s))
            {
                Stack_deinit(&s);
                return false;
            } 
            else 
            {
                int openBr = Stack_pop(&s);
                if (brTypeEquals(openBr, *ch) == false) 
                {
                    Stack_deinit(&s);
                    return false;
                }
            }
        } 
        else 
        { // open
            Stack_push(&s, *ch);
        }

        ch += 1;
    }

    if (Stack_isEmpty(&s))
    {
        Stack_deinit(&s);
        return true;
    }
    else 
    {
        Stack_deinit(&s);
        return false;
    }
}

int main()
{
    assert(isBalanced("") == true);
    assert(isBalanced("()") == true);
    assert(isBalanced("{}") == true);
    assert(isBalanced("[]") == true);
    assert(isBalanced("<>") == true);
    assert(isBalanced("(<>)") == true);
    assert(isBalanced("({}[])") == true);
    assert(isBalanced("(") == false);
    assert(isBalanced(")") == false);
    assert(isBalanced("({)}") == false);
    assert(isBalanced("()(") == false);
    assert(isBalanced("([)") == false);
    assert(isBalanced("({[<") == false);

    return 0;
}