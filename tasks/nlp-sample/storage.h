#ifndef STORAGE_H
#define STORAGE_H

#include <list.h>

/**
**/
List * Storage_loadNumbers(const char * fileName);
void Storage_saveResult(const char * fileName, List * result);

#endif