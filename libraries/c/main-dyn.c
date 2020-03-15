#include <stdlib.h>
#include <stdio.h>
#define _GNU_SOURCE // this is required before dlfcn.h
#include <dlfcn.h>

// just help for function pointers, it not required
typedef void (*VoidFunc)(void);

int main(void) {
	puts("Call main()");
	// path to shared object
	const char * soName = "./libdynamic.so";
	// load/open shared object
	void * soHandle = dlopen(soName, RTLD_LAZY);
	if (soHandle) {
		// obtain function pointer from shared object
		VoidFunc func = (VoidFunc) dlsym(soHandle, "static_lib_func");  
		if (func) {
			func();  // call function via pointer
		} else {
			puts("Error pointer function");
		}
		// unload/close shared object
		dlclose(soHandle);
	} else {
		puts("Error opening so");
	}
	return 0;
}
