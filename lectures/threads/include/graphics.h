#pragma once

typedef struct Graphics Graphics;

typedef struct Vec2D Vec2D;
struct Vec2D {
	double x;
	double y;
};

typedef int ConsoleColor;

void Graphics_drawPixel(Graphics * self, Vec2D pos, ConsoleColor color);
void Graphics_drawLine(Graphics * self, Vec2D start, Vec2D end, ConsoleColor color);
void Graphics_drawCircle(Graphics * self, Vec2D pos, double radius, ConsoleColor color);
