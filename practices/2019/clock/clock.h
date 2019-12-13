#pragma once

#include <time.h>

struct Point
{
    int x;
    int y;
};

struct Color
{
    int red;
    int green;
    int blue;
};

struct ClockHand
{
    float length;
    float angle;
    struct Color color;
};

struct Clock
{
    struct ClockHand hands[3];
    struct Point center;
    float size;
};

void updateClock(struct Clock *clock, time_t *t);

void drawClock(struct Clock *clock);
