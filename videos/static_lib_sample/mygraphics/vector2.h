// add this on top
#pragma once

// vector2 module interface
// new types
struct Vector2
{
    double x;
    double y;
};

// global variables
static const struct Vector2 Vector2_empty = {0, 0};

// prototypes
double Vector2_length(struct Vector2 a);
struct Vector2 Vector2_add(struct Vector2 a, struct Vector2 b);

// ;