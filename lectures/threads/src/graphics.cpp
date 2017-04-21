#include <math.h>

#include <progbase-cpp/console.h>

#include <graphics.h>

static inline void swap(double * a, double * b);

void Graphics_drawPixel(Graphics * self, Vec2D pos, ConsoleColor color) {
    progbase::console::Console::setCursorPosition(pos.y, pos.x);
    progbase::console::Console::setCursorAttribute(color);
    putchar(' ');
}

void Graphics_drawLine(Graphics * self, Vec2D start, Vec2D end, ConsoleColor color) {
    double x0 = start.x;
    double x1 = end.x;
    double y0 = start.y;
    double y1 = end.y;

    int steep = fabs(y1 - y0) > fabs(x1 - x0);
    if (steep) {
        swap(&x0, &y0);
        swap(&x1, &y1);
    }

    double dx = fabs(x1 - x0);
    double dy = fabs(y1 - y0);
    double error = 0;
    double dErr = dy;
    double x = x0;
    double y = y0;
    Graphics_drawPixel(
        self, 
        (Vec2D){ steep ? y : x, steep ? x : y },
        color);

    int xstep = (x0 < x1) ? 1 : -1;
    int ystep = (y0 < y1) ? 1 : -1;
    while(fabs(x - x1) > 1) {
        x += xstep;
        error += dErr;
        if (2 * error > dx) {
            y += ystep;
            error -= dx;
        }
        Graphics_drawPixel(
            self, 
            (Vec2D){ steep ? y : x, steep ? x : y },
            color);
    }
}

void Graphics_drawCircle(Graphics * self, Vec2D pos, double radius, ConsoleColor color) {
    double x0 = pos.x;
    double y0 = pos.y;
    double x = radius;
    double y = 0;
    double err = 0;

    while (x >= y)
    {
        Graphics_drawPixel(self, (Vec2D){x0 + x, y0 + y}, color);
        Graphics_drawPixel(self, (Vec2D){x0 + y, y0 + x}, color);
        Graphics_drawPixel(self, (Vec2D){x0 - y, y0 + x}, color);
        Graphics_drawPixel(self, (Vec2D){x0 - x, y0 + y}, color);
        Graphics_drawPixel(self, (Vec2D){x0 - x, y0 - y}, color);
        Graphics_drawPixel(self, (Vec2D){x0 - y, y0 - x}, color);
        Graphics_drawPixel(self, (Vec2D){x0 + y, y0 - x}, color);
        Graphics_drawPixel(self, (Vec2D){x0 + x, y0 - y}, color);

        if (err <= 0)
        {
            y += 1;
            err += 2*y + 1;
        }
        if (err > 0)
        {
            x -= 1;
            err -= 2*x + 1;
        }
    }
}

static inline void swap(double * a, double * b) {
    double t = *a;
    *a = *b;
    *b = t;
}
