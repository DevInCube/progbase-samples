#ifndef MODULE_H
#define MODULE_H

#include <stdbool.h>

// paste your module interface here

typedef struct CsvRow CsvRow;
typedef struct CsvDoc CsvDoc;

CsvRow * CsvRow_new(void);

CsvDoc * CsvDoc_newFromFile(const char * filePath);
void CsvDoc_free(CsvDoc ** selfPtr);
void CsvDoc_writeToFile(CsvDoc * self, const char * filePath);

CsvRow * CsvDoc_getRow(CsvDoc * self);
bool CsvDoc_moveNext(CsvDoc * self);
void CsvDoc_reset(CsvDoc * self);

void CsvDoc_addRow(CsvDoc * self, CsvRow * row);

const char * CsvRow_getRow(CsvRow * self);
bool CsvRow_moveNext(CsvRow * self);
void CsvRow_reset(CsvRow * self);

void CsvRow_addValue(CsvRow * self, const char * value);

#endif
