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

void drawTriangle(Point p, float size)
{
    if (size < 5) return;
    float h = sqrt(size * size - (size / 2 * size / 2));
    Canvas_strokeLine(p.x - size / 2, p.y - h / 2, p.x + size / 2, p.y - h / 2);
    Point ph = {p.x, p.y + h / 2};
    Canvas_strokeLine(p.x - size / 2, p.y - h / 2, ph.x, ph.y);
    Canvas_strokeLine(p.x + size / 2, p.y - h / 2, ph.x, ph.y);
    //
    Point p1 = {p.x, p.y + h / 4};
    Canvas_putPixel(p1.x , p1.y);
    Point p2 = {p.x - size / 4, p.y - h / 4};
    Canvas_putPixel(p2.x , p2.y);
    Point p3 = {p.x + size / 4, p.y - h / 4};
    Canvas_putPixel(p3.x , p3.y);
    //
    drawTriangle(p1, size / 2);
    drawTriangle(p2, size / 2);
    drawTriangle(p3, size / 2);
}

int main()
{
    int w = 300;
    int h = w;
    Canvas_setSize(w, h);
    Canvas_invertYOrientation();
    Point o = {w / 2, h / 2};
    Canvas_beginDraw();
    Canvas_setColorRGB(0xff, 0xff, 0xff);
    drawTriangle(o, w - 10);
    Canvas_endDraw();
    return 0;
}
