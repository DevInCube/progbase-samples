#include <stdlib.h>
#include <stdio.h>

#include "staticlib/lib.h"

int main(void) {
	puts("Call main()");
	static_lib_func();
	return 0;
}
