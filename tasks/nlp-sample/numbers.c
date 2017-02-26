#include <numbers.h>
#include <stdlib.h>
#include <stdio.h>

/* type implementation */
struct Number {
	int value;
	int base;
};

Number * Number_new(int value, int base) {
	Number * self = malloc(sizeof(struct Number));
	self->value = value;
	self->base = base;
	return self;
}

Number * Number_newFromString(const char * str) {
	/* @todo implement string parse */
	int value = 0;  // fake data
	int base = 0;  // fake data
	return Number_new(value, base);
}

void Number_free(Number ** selfPtr) {
	free(*selfPtr);
	*selfPtr = NULL;
}

int Number_getValue(Number * self) {
	return self->value;
}

int Number_getBase(Number * self) {
	return self->base;
}

char * Number_toString(Number * self, char * buffer) {
	sprintf(buffer, "%i (%i)", self->value, self->base);
	return buffer;
}
