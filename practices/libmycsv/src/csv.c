#include <csv.h>
#include <stdlib.h>

// paste your module implementation here

// typedef struct CsvRow CsvRow;
// typedef struct CsvDoc CsvDoc;

CsvRow * CsvRow_new(void) {
	return NULL;
}

CsvDoc * CsvDoc_newFromFile(const char * filePath) {
	return NULL;
}

void CsvDoc_free(CsvDoc ** selfPtr) {

}

void CsvDoc_writeToFile(CsvDoc * self, const char * filePath) {

}


CsvRow * CsvDoc_getRow(CsvDoc * self) { return NULL; }
bool CsvDoc_moveNext(CsvDoc * self) {return false;}
void CsvDoc_reset(CsvDoc * self) {}

void CsvDoc_addRow(CsvDoc * self, CsvRow * row){}

const char * CsvRow_getRow(CsvRow * self){return NULL;}
bool CsvRow_moveNext(CsvRow * self){return false;}
void CsvRow_reset(CsvRow * self){}

void CsvRow_addValue(CsvRow * self, const char * value){}