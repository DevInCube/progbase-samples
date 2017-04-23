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

void print(char & symb, CursorAttributes color,  mutex & g_mutex) {
	while (1) {
		g_mutex.lock();
		Console::setCursorAttribute(color);
		cout << symb << flush;
		g_mutex.unlock();
		this_thread::sleep_for(chrono::milliseconds(100));
	}
}

void drawCircle() {

	// g_m.lock();
	// double rad = 5 * time * M_PI / 180.0;
	// time++;
	// clearRect((Vec2D){0, 0}, (Vec2D){40, 24});
	// Graphics_drawCircle(NULL, (Vec2D){20, 12}, 5 + 3 * cosf(rad), CursorAttributes::BG_YELLOW);
	// g_m.unlock();
}

mutex m;

void printRotatedCircle(
	Vec2D consoleCenter, 
	double rotateRadius,
	double radius,
	double amp,
	double radians,
	double dir
	) 
{
	double r = amp * sinf(radians);
	Vec2D rotateVector = (Vec2D){1, 1};
	rotateVector = Vec2D_normalize(rotateVector);
	rotateVector = Vec2D_multByNumber(rotateVector, rotateRadius);
	rotateVector = Vec2D_rotate(rotateVector, dir * radians);
	Vec2D circleCenter = Vec2D_add(consoleCenter, rotateVector);
	m.lock();
	Graphics_drawCircle(
		NULL, 
		circleCenter, 
		radius + r, 
		CursorAttributes::BG_YELLOW);
	m.unlock();
}

void threadf(double & dir) {
	Vec2D consoleCenter = (Vec2D){40, 12};
	double rotateRadius = 5;
	const int amp = 2;
	double radius = 5;
	int degrees = 0;
	while (1) {
		m.lock();
		Console::setCursorAttribute(CursorAttributes::BG_DEFAULT);
		Console::clear();
		m.unlock();
		double radians = degrees * M_PI / 180.0;
		printRotatedCircle(
			consoleCenter,
			rotateRadius,
			radius,
			amp,
			radians,
			dir
		);
		degrees++;
	}
}

int main(void) {

	double d1 = -2;
	double d2 = 3;
	thread t1(threadf, ref(d1));
	thread t2(threadf, ref(d2));

	int x;
	cin >> x;
	

	// Graphics_drawLine(
	// 	NULL,
	// 	(Vec2D){0, 0},
	// 	(Vec2D){80, 24},
	// 	CursorAttributes::BG_RED
	// );

	Console::reset();
	// mutex m;
	// char symb[] = { 'R', 'G', 'B' };
	// CursorAttributes colors[] = {
	// 	CursorAttributes::BG_RED,
	// 	CursorAttributes::BG_GREEN,
	// 	CursorAttributes::BG_BLUE
	// };
	// thread bThread(print, std::ref(symb[0]), std::ref(colors[0]), std::ref(m));
	// thread cThread(print, std::ref(symb[1]), std::ref(colors[1]), std::ref(m));
	// thread dThread(print, std::ref(symb[2]), std::ref(colors[2]), std::ref(m));

	// while (1) {
	// 	// g_mutex.lock();
	// 	// Console::setCursorAttribute(CursorAttributes::BG_BLUE);
	// 	// cout << "A" << flush;
	// 	// g_mutex.unlock();
	// 	this_thread::sleep_for(chrono::milliseconds(100));
	// }

	

	return 0;
}

// static mutex g_m;

// void clearRect(Vec2D location, Vec2D size) {
// 	for (int y = 0; y < size.y; y++) {
// 		for (int x = 0; x < size.x; x++) {
// 			Vec2D pos = { location.x + x, location.y + y };
// 			Graphics_drawPixel(NULL, pos, CursorAttributes::BG_BLACK);
// 		}
// 	}
// }

// void threadA() {
// 	long time = 0;
// 	while (true) {
// 		g_m.lock();
// 		double rad = 5 * time * M_PI / 180.0;
// 		time++;
// 		clearRect((Vec2D){0, 0}, (Vec2D){40, 24});
// 		Graphics_drawCircle(NULL, (Vec2D){20, 12}, 5 + 3 * cosf(rad), CursorAttributes::BG_YELLOW);
// 		g_m.unlock();
// 		this_thread::sleep_for(chrono::milliseconds(10));
// 	}
// }

// void threadB() {
// 	long time = 0;
// 	while (true) {
// 		g_m.lock();
// 		double rad = 2 * time * M_PI / 180.0;
// 		time++;
// 		clearRect((Vec2D){40, 0}, (Vec2D){40, 24});
// 		Graphics_drawCircle(NULL, (Vec2D){60, 12}, 5 + 3 * sinf(rad), CursorAttributes::BG_CYAN);
// 		g_m.unlock();
// 		this_thread::sleep_for(chrono::milliseconds(10));
// 	}
// }

// int main(void) {
// 	Console::clear();
// 	// Console::setCursorAttribute(CursorAttributes::BG_CYAN);
// 	// Console::setCursorAttribute(CursorAttributes::FG_BLACK);
// 	// cout << "*" << endl;
// 	// Console::reset();
// 	// cout << Console::getChar() << endl;
// 	thread a(threadA);
// 	thread b(threadB);

// 	while (!Console::isKeyDown()) { }  // to lock main thread
	
// 	a.detach();
// 	b.detach();
// 	Console::reset();
// 	cout << endl;
// 	return 0;
// }
