#include "parser.h"
#include <stdio.h>

typedef struct
{
    List *tokens;
    int currentTokenIndex;
    char *error; // error string
    // @todo optional extra fields (text position, etc.)
} Parser;

// check current token type
bool accept(Parser *self, TokenType tokenType);
// expect exactly that token type or fail
bool expect(Parser *self, TokenType tokenType);

static bool Parser_file(Parser *self);
static bool Parser_record(Parser *self);
static bool Parser_field(Parser *self);

static bool Parser_NON_ESCAPED(Parser *self);
static bool Parser_ESCAPED(Parser *self);
static bool Parser_COMMA(Parser *self);
static bool Parser_CRLF(Parser *self);

static bool Parser_file(Parser *self)
{
    printf("%s\n", __func__);
    if (!Parser_record(self))
    {
        return false;
    }
    while (accept(self, TokenType_CRLF))
    {
        if (!Parser_record(self))
        {
            return false;
        }
    }
    return true;
}
static bool Parser_record(Parser *self)
{
    printf("%s\n", __func__);
    if (!Parser_field(self))
    {
        return false;
    }
    while (accept(self, TokenType_COMMA))
    {
        if (!Parser_field(self))
        {
            return false;
        }
    }
    return true;
}
static bool Parser_field(Parser *self)
{
    printf("%s\n", __func__);
    if (accept(self, TokenType_ESCAPED))
    {
        return true;
    }
    else
    {
        return Parser_NON_ESCAPED(self);
    }
}

static bool Parser_NON_ESCAPED(Parser *self)
{
    printf("%s\n", __func__);
    return expect(self, TokenType_NON_ESCAPED);
}
static bool Parser_ESCAPED(Parser *self)
{
    printf("%s\n", __func__);
    return expect(self, TokenType_ESCAPED);
}
static bool Parser_COMMA(Parser *self)
{
    printf("%s\n", __func__);
    return expect(self, TokenType_COMMA);
}
static bool Parser_CRLF(Parser *self)
{
    printf("%s\n", __func__);
    return expect(self, TokenType_CRLF);
}

// check current token type
bool accept(Parser *self, TokenType tokenType)
{
    if (self->currentTokenIndex == List_size(self->tokens)) return false;
    Token * token = List_get(self->tokens, self->currentTokenIndex);
    bool res = (token->type == tokenType);
    if (res)
    {
        printf("%s ", __func__);
        Token_print(token);
        printf("\n");
        self->currentTokenIndex += 1;
    }
    return res;
}
// expect exactly that token type or fail
bool expect(Parser *self, TokenType tokenType)
{
    if (self->currentTokenIndex == List_size(self->tokens)) return false;
    Token * token = List_get(self->tokens, self->currentTokenIndex);
    if (token->type != tokenType)
    {
        fprintf(stderr, "Unexpected token %i. Expected %i\n", token->type, tokenType);
        abort();
    }
    printf("%s ", __func__);
    Token_print(token);
    printf("\n");
    self->currentTokenIndex += 1;
    return true;
}

//

bool Parser_match(List * tokens)
{
    Parser parser;
    parser.tokens = tokens;
    parser.error = NULL;
    parser.currentTokenIndex = 0;
    return Parser_file(&parser);
}