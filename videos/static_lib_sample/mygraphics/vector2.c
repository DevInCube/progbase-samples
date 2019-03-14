#include "vector2.h"

#include <math.h>

// vector2 module implementation

double Vector2_length(struct Vector2 a)
{
    return sqrt(pow(a.x, 2) + pow(a.y, 2));
}

struct Vector2 Vector2_add(struct Vector2 a, struct Vector2 b)
{
    return (struct Vector2){ a.x + b.x, a.y + b.y };
}

// ;