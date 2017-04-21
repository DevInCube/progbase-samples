#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <thread>
#include <mutex>

#include <progbase.h>
#include <progbase-cpp/console.h>

#include <graphics.h>

using namespace std;
using namespace progbase::console;

static mutex g_m;

void clearRect(Vec2D location, Vec2D size) {
	for (int y = 0; y < size.y; y++) {
		for (int x = 0; x < size.x; x++) {
			Vec2D pos = { location.x + x, location.y + y };
			Graphics_drawPixel(NULL, pos, CursorAttributes::BG_BLACK);
		}
	}
}

void threadA() {
	long time = 0;
	while (true) {
		g_m.lock();
		double rad = 5 * time * M_PI / 180.0;
		time++;
		clearRect((Vec2D){0, 0}, (Vec2D){40, 24});
		Graphics_drawCircle(NULL, (Vec2D){20, 12}, 5 + 3 * cosf(rad), CursorAttributes::BG_YELLOW);
		g_m.unlock();
		this_thread::sleep_for(chrono::milliseconds(10));
	}
}

void threadB() {
	long time = 0;
	while (true) {
		g_m.lock();
		double rad = 2 * time * M_PI / 180.0;
		time++;
		clearRect((Vec2D){40, 0}, (Vec2D){40, 24});
		Graphics_drawCircle(NULL, (Vec2D){60, 12}, 5 + 3 * sinf(rad), CursorAttributes::BG_CYAN);
		g_m.unlock();
		this_thread::sleep_for(chrono::milliseconds(10));
	}
}

int main(void) {
	Console::clear();
	// Console::setCursorAttribute(CursorAttributes::BG_CYAN);
	// Console::setCursorAttribute(CursorAttributes::FG_BLACK);
	// cout << "*" << endl;
	// Console::reset();
	// cout << Console::getChar() << endl;
	thread a(threadA);
	thread b(threadB);

	while (!Console::isKeyDown()) { }  // to lock main thread
	
	a.detach();
	b.detach();
	Console::reset();
	cout << endl;
	return 0;
}
