#include <stdlib.h>
#include <stdio.h>
#include <progbase.h>
#include <progbase/console.h>
#include <time.h>

const float METRIC = 10.0;

struct Point2D {
    float x;
    float y;
};

struct Ball {
    struct Point2D loc;
    struct Point2D vel;
    enum conAttribute_e color;
};

struct Ball updateBall(struct Ball ball, int t, struct Point2D size);
void drawBall(struct Ball ball);

int main(void) {
    srand(time(0));
    Console_clear();
    struct ConsoleSize consoleSize = Console_size();
    int maxRows = consoleSize.rows;

    struct Point2D worldSize = {
        consoleSize.columns * METRIC,
        consoleSize.rows * METRIC
    };
    const int len = 10;
    struct Ball balls[len];
    for (int i = 0; i < len; i++) {
        balls[i].loc.x = rand() % (int)worldSize.x;
        balls[i].loc.y = rand() % (int)worldSize.y;
        balls[i].vel.x = rand() % 1000 - 500;
        balls[i].vel.y = rand() % 1000 - 500;
        balls[i].color = rand() % 7 + 101;
    }
    const int sleep = 33;
    while (1) {
        Console_reset();
        Console_clear();
        for (int i = 0; i < len; i++) {
            drawBall(balls[i]);
            balls[i] = updateBall(balls[i], sleep, worldSize);
        }
        sleepMillis(sleep);
    }

    Console_reset();
    Console_setCursorPosition(maxRows - 1, 0);
    return 0;
}

void drawBall(struct Ball ball) {
    int row = ball.loc.y / METRIC;
    int col = ball.loc.x / METRIC;
    Console_setCursorPosition(row, col);
    Console_setCursorAttribute(ball.color);
    putchar(' ');
    fflush(stdout);
}

struct Ball updateBall(struct Ball ball, int t, struct Point2D size) {
    ball.loc.x = ball.loc.x + ball.vel.x * t/1000.0;
    if (ball.loc.x  < 0 || ball.loc.x > size.x) {
        ball.vel.x = -ball.vel.x;
    }
    ball.loc.y = ball.loc.y + ball.vel.y * t/1000.0;
    if (ball.loc.y < 0 || ball.loc.y > size.y) {
        ball.vel.y = -ball.vel.y;
    }
    return ball;
}
