#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
//
#include <list.h>

int main()  
{
    List list; 
    List_init(&list);
    List_add(&list, NULL);
    List_add(&list, NULL);
    printf("List: %i\n", List_size(&list));
    return 0;
}