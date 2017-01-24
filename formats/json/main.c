#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <jansson.h>

int main(void) {
	const char * text = "{}";
	json_error_t error;
	json_t * root = json_loads(text, 0, &error);
	assert(json_is_object(root));
	return 0;
}
