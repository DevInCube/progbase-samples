#include <convert.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Composition {
	char author[100];
	char title[100];
	int lengthSeconds;
};

Composition * Composition_new(char * author, char * title, int len) {
	Composition * self = malloc(sizeof(Composition));
	strcpy(self->author, author);
	strcpy(self->title, title);
	self->lengthSeconds = len;
	return self;
}

void Composition_free(Composition ** selfPtr){ 
	free(*selfPtr);
	*selfPtr = NULL;
}

void Composition_print(Composition * self) {
	printf("Title: %s\nAuthor: %s\nLength: %i\n",
		self->title,
		self->author,
		self->lengthSeconds);
}

char * Composition_toString(Composition * self, char * buffer) {
	sprintf(buffer, "%s;%s;%i.", 
		self->author, 
		self->title, 
		self->lengthSeconds);
	return buffer;
}

Composition * Composition_newFromString(const char * str) {
	Composition * self = Composition_new("", "", 0);
	sscanf(str, "%s;%s;%i.", 
		self->author, 
		self->title,
		&(self->lengthSeconds));
	return self;
}


