// gcc -g main.c -lprogbase -lm
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
// libprogbase
#include <progbase.h>
#include <progbase/console.h>
#include <progbase/canvas.h>

#include "list.h"
#include "lexer.h"
#include "parser.h"

int main()
{
    //const char *csvString = "12,John Wick,KP-99,100\n33,\"Jude, Law\",KP-98,99";
    const char *csvString = "12,John Wick,KP-99,100\n33,Jude Law,KP-98,99";
    // 
    List tokens;
    List_init(&tokens);

    Lexer_splitTokens(csvString, &tokens);
    Lexer_printTokens(&tokens);

    printf("\n\nParser: %s\n", Parser_match(&tokens) ? "true" : "false");

    Lexer_clearTokens(&tokens);

    List_deinit(&tokens);
    //
    puts("\n---");
    return 0;
}