#ifndef STORAGE_H
#define STORAGE_H

#include <numbers.h>

/**
**/
Sequence * Storage_loadNumbers(const char * fileName);
void Storage_saveResult(const char * fileName, Sequence * result);

#endif