#pragma once

typedef struct Graphics Graphics;

typedef struct Vec2D Vec2D;
struct Vec2D {
	double x;
	double y;
};

typedef enum ConsoleColor {
	// @todo
} ConsoleColor;

void Graphics_drawPixel(Graphics * self, double x, double y, ConsoleColor color);
void Graphics_drawLine(Graphics * self, Vec2D start, Vec2D end, ConsoleColor color);
