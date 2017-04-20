#pragma once

typedef struct Graphics Graphics;

typedef struct {
	double x, y;
} Vec2D;

typedef enum {

} ConsoleColor;

void Graphics_drawPixel(Graphics * self, double x, double y, ConsoleColor color);
void Graphics_drawLine(Graphics * self, Vec2D start, Vec2D end, ConsoleColor color);
