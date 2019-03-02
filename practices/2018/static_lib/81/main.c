// gcc -g main.c -lprogbase -lm
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#include <list.h>

int main()
{
    List list; 
    List_init(&list);
    List_deinit(&list);
    puts("\n---");
    return 0;
}