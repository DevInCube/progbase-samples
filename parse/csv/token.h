#pragma once

#include <stdbool.h>

typedef enum {
    TokenType_NON_ESCAPED,
    TokenType_ESCAPED,
    TokenType_COMMA,
    TokenType_CRLF,
} TokenType;

typedef struct __Token Token;
struct __Token 
{
    TokenType type;
    const char * lexeme;
};

Token * Token_alloc(TokenType type, const char *lexeme);
void Token_free(Token * self);

void Token_print(Token * self);