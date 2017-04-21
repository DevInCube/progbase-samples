#include <stdlib.h>
#include <stdio.h>
#include <thread>
#include <mutex>

#include <progbase.h>
#include <progbase-cpp/console.h>

#include <graphics.h>

using namespace std;
using namespace progbase::console;

static mutex g_m;

void threadA() {
	while (true) {
		g_m.lock();
		Console::setCursorAttribute(CursorAttributes::BG_CYAN);
		cout << "A" << flush;
		g_m.unlock();
		this_thread::sleep_for(chrono::milliseconds(10));
	}
}

void threadB() {
	while (true) {
		g_m.lock();
		Console::setCursorAttribute(CursorAttributes::BG_BLACK);
		cout << "." << flush;
		g_m.unlock();
		this_thread::sleep_for(chrono::milliseconds(10));
	}
}

int main(void) {
	Console::clear();
	Graphics_drawCircle(NULL, (Vec2D){40, 12}, 10, CursorAttributes::BG_CYAN);
	Console::setCursorPosition(0, 0);
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
