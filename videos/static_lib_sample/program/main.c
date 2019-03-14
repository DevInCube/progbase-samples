#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>  // in Linux add -lm on compile

#include "vector2.h"
#include "extra.h"

int main(void)
{
    struct Vector2 v1 = Vector2_empty;
    struct Vector2 v2 = { 10, 10 };

    Extra_printVector2(v1);
    Extra_printVector2(v2);

    double v1Len = Vector2_length(v1);
    printf("|v1|: %lf\n", v1Len);
    printf("|v2|: %lf\n", Vector2_length(v2));
    
    struct Vector2 vsum = Vector2_add(v1, v2);
    printf("|vsum|: %lf\n", Vector2_length(vsum));
    printf("|vsum2|: %lf\n", Vector2_length(Vector2_add(v2, v2)));
    return 0;
}