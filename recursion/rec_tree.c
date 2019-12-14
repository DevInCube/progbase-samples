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

const float PI = 3.141592;

typedef struct
{
    float x;
    float y;
} Point;

void drawTrunc(Point p, float length, float angle)
{
    if (length < 1) {
        Canvas_setColorRGB(0, 0xff, 0xff);
        Canvas_putPixel(p.x, p.y);
        return;
    }
    Point p2 = {
        p.x + length * cos(angle),
        p.y + length * sin(angle)};
    Canvas_setColorRGB(0xff, 0xff, 0xff);
    Canvas_strokeLine(p.x, p.y, p2.x, p2.y);
    //sleepMillis(100);
    float nextLength = length / sqrt(2);
    float angle1 = angle + PI / 6;
    float angle2 = angle - PI / 6;
    drawTrunc(p2, nextLength, angle1);
    drawTrunc(p2, nextLength, angle2);
}

int main()
{
    int w = 100;
    int h = w;
    Canvas_setSize(w, h);
    Canvas_invertYOrientation();
    Point o = {w / 2, 0};
    Canvas_beginDraw();
    drawTrunc(o, 20, PI / 2);
    Canvas_endDraw();
    return 0;
}
