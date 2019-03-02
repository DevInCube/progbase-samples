#include "lexer.h"
#include "token.h"
#include <string.h>

char * strOnHeap(const char * str)
{
    char * m = malloc(strlen(str) + 1);
    strcpy(m, str);
    return m;
}

int  Lexer_splitTokens(const char * input, List * tokens)
{
    const char * p = input;
    char buf[100];
    int bufX = 0;
    while (1) 
    {
        if (*p == ',' || *p == '\n' || *p == '\0')
        {
            buf[bufX] = '\0';
            bufX = 0;
            List_add(tokens, Token_alloc(TokenType_NON_ESCAPED, strOnHeap(buf)));
        }
        else
        {
            buf[bufX++] = *p;
        }
        
        if (*p == ',') 
        {
            List_add(tokens, Token_alloc(TokenType_COMMA, NULL));
        }
        else if (*p == '\n')
        {
            List_add(tokens, Token_alloc(TokenType_CRLF, NULL));
        }
        if (*p == '\0')
        {
            break;
        }
        p += 1;
    }
    return 0;
}
void Lexer_clearTokens(List * tokens)
{
    for (int i = 0; i < List_size(tokens); i++)
    {
        Token * token = List_get(tokens, i);
        Token_free(token);
    }
}

void Lexer_printTokens(List * tokens)
{
    for (int i = 0; i < List_size(tokens); i++)
    {
        Token * token = List_get(tokens, i);
        Token_print(token);
    }
}