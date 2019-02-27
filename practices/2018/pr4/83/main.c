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

int main()
{
    const char *csvString = "12,John Wick,KP-99,100\n33,Jude Law,KP-98,99";
    // parse CSV and output
    const char *p = csvString;
    char buf[100];
    int bufX = 0;
    while (1)
    {
        if (*p == ',' || *p == '\n' || *p == '\0')
        {
            buf[bufX] = '\0';
            printf("[%s]", buf);
            if (*p == '\n' || *p == '\0')
            {
                printf("\n");
            }
            bufX = 0;
        }
        else
        {
            buf[bufX] = *p;
            bufX += 1;
        }
        if (*p == '\0')
        {
            break;
        }
        p += 1;
    }
    //
    puts("\n---");
    return 0;
}