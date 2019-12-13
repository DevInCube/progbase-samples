#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <progbase.h>
#include <progbase/console.h>
#include <progbase/canvas.h>

#include "clock.h"

const float PI = 3.141592;

void updateClock(struct Clock *clock, time_t *t)
{
    struct tm *t2 = localtime(t);
    //
    clock->hands[0].angle = PI / 2 - (2 * PI / 12) * (t2->tm_hour + t2->tm_min / 60.0);
    clock->hands[1].angle = PI / 2 - 2 * PI / 60 * t2->tm_min;
    clock->hands[2].angle = PI / 2 - 2 * PI / 60 * t2->tm_sec;
}

void drawClock(struct Clock *clock)
{
    Canvas_setColorRGB(0, 128, 0);
    Canvas_fillCircle(clock->center.x, clock->center.y, clock->size / 2);
    Canvas_setColorRGB(0, 255, 0);
    Canvas_strokeCircle(clock->center.x, clock->center.y, clock->size / 2);
    for (int i = 0; i < 12; i++)
    {
        float angle = 2 * PI / 12 * i;
        float hourLength = clock->size / 2;
        Canvas_strokeLine(clock->center.x + (hourLength - 5) * cos(angle),
                          clock->center.y + (hourLength - 5) * sin(angle),
                          clock->center.x + (hourLength - 2) * cos(angle),
                          clock->center.y + (hourLength - 2) * sin(angle));
    }
    for (int i = 0; i < 3; i++)
    {
        struct ClockHand *phand = &clock->hands[i];
        Canvas_setColorRGB(phand->color.red, phand->color.green, phand->color.blue);
        Canvas_strokeLine(clock->center.x, clock->center.y,
                          clock->center.x + phand->length * cos(phand->angle),
                          clock->center.y + phand->length * sin(phand->angle));
    }
}
