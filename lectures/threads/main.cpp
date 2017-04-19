#include <stdlib.h>
#include <stdio.h>

#include <progbase-cpp/console.h>

using namespace std;
using namespace progbase::console;

int main(void) {
	Console::clear();
	Console::setCursorPosition(10, 10);
	Console::setCursorAttribute(CursorAttributes::BG_CYAN);
	Console::setCursorAttribute(CursorAttributes::FG_BLACK);
	cout << "*" << endl;
	Console::reset();
	cout << Console::getChar() << endl;
	return 0;
}
