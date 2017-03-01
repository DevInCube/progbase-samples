#include <numbers.h>
#include <stdlib.h>
#include <stdio.h>
#include <list.h>
#include <object.h>

/* type implementation */
struct Number {
	implements(Object);
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
	sprintf(buffer, "%i(%i)", self->value, self->base);
	return buffer;
}

struct Sequence {
	List * numbers;
};

Sequence * Sequence_new(void) {
	Sequence * self = malloc(sizeof(struct Sequence));
	self->numbers = List_new();
	return self;
}

void Sequence_free(Sequence ** selfPtr) {
	Sequence * self = *selfPtr;
	List_free(&self->numbers);
	free(self);
	*selfPtr = NULL;
}

void Sequence_add(Sequence * self, Number * number) {
	List_add(self->numbers, number);
}

int Sequence_count(Sequence * self) {
	return List_count(self->numbers);
}

Number * Sequence_get(Sequence * self, int index) {
	return (Number *)List_get(self->numbers, index);
}
