#ifndef CONVERT_H
#define CONVERT_H

#include <stdlib.h>

typedef struct Composition Composition;

Composition * Composition_new(char * author, char * title, int len);
void Composition_free(Composition ** selfPtr);

void Composition_print(Composition * self);

char * Composition_toString(Composition * self, char * buffer);
Composition * Composition_newFromString(const char * str);

#endif