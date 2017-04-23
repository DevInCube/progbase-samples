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

Vec2D Vec2D_multByNumber(Vec2D a, double number) {
    return (Vec2D){
        .x = a.x * number,
        .y = a.y * number
    };
}

Vec2D Vec2D_rotate(Vec2D self, double radians) {
    double ca = cosf(radians);
    double sa = sinf(radians);
    return (Vec2D) {
        .x = ca * self.x - sa * self.y,
        .y = sa * self.x + ca * self.y
    };
}

Vec2D Vec2D_normalize(Vec2D self) {
    double length = Vec2D_length(self);
    if (length == 0) return self;
    return Vec2D_multByNumber(self, 1.0 / length);
}

double Vec2D_length(Vec2D self) {
    return sqrt(self.x * self.x + self.y * self.y);
}

Vec2D Vec2D_add(Vec2D a, Vec2D b) {
    return (Vec2D){
        .x = a.x + b.x,
        .y = a.y + b.y
    };
}

Vec2D Vec2D_substract(Vec2D a, Vec2D b) {
    return (Vec2D){
        .x = a.x - b.x,
        .y = a.y - b.y
    };
}
