#pragma once

#include "list.h"

int  Lexer_splitTokens(const char * input, List * tokens);
void Lexer_clearTokens(List * tokens);

void Lexer_printTokens(List * tokens);