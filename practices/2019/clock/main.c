#include <time.h>
#include <stdbool.h>
#include <progbase.h>
#include <progbase/console.h>
#include <progbase/canvas.h>

#include "clock.h"

int main()
{
    int w = 40;
    int h = w;
    struct Clock c = {
        .size = w,
        .center = {w / 2, h / 2},
        .hands = {
            {.length = w / 4, .color = {0, 255, 128}},
            {.length = w / 2 - 5, .color = {0, 255, 255}},
            {.length = w / 2 - 3, .color = {0, 0, 255}}}};

    Console_clear();
    Canvas_setSize(w, h);
    Canvas_invertYOrientation();
    while (true)
    {
        // update
        time_t t1 = time(NULL);
        updateClock(&c, &t1);
        // draw
        Canvas_beginDraw();
        drawClock(&c);
        Canvas_endDraw();
        //
        sleepMillis(1000);
    }
}
