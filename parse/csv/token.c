#include "token.h"
#include <stdlib.h>
#include <stdio.h>

Token * Token_alloc(TokenType type, const char *lexeme)
{
    Token * self = malloc(sizeof(Token));
    self->type = type;
    self->lexeme = lexeme;
    return self;
}
void Token_free(Token * self)
{
    free(self); 
}

void Token_print(Token * self)
{
    printf("<");
    switch (self->type)
    {
        case TokenType_COMMA: printf(","); break;
        case TokenType_CRLF: printf("\\n"); break;
        case TokenType_NON_ESCAPED: printf("NON_ESCAPED, \"%s\"", self->lexeme); break;
        case TokenType_ESCAPED: printf("ESCAPED, \"%s\"", self->lexeme); break;
    }
    printf(">");
}