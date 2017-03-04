#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <list.h>

#include <csv.h>
#include <fs.h>
// paste your module implementation here

struct CsvRow {
	List * values;
	int position;
};

struct CsvDoc {
	List * rows;
	int position;
};

CsvDoc * CsvDoc_new(void) { 
	CsvDoc * self = malloc(sizeof(CsvDoc));
	self->rows = List_new();
	self->position = -1;
	return self;
}

CsvRow * CsvRow_new(void) { 
	CsvRow * self = malloc(sizeof(CsvRow));
	self->values = List_new();
	self->position = -1;
	return self;
}

void CsvRow_free(CsvRow ** selfPtr) {
	CsvRow * self = *selfPtr;
	for (int i = 0; i < List_count(self->values); i++) {
		char * value = List_get(self->values, i);
		free(value);
	}
	List_free(&self->values);
	free(self);
	*selfPtr = NULL;
}

void CsvDoc_free(CsvDoc ** selfPtr) {
	CsvDoc * self = *selfPtr;
	for (int i = 0; i < List_count(self->rows); i++) {
		CsvRow * row = List_get(self->rows, i);
		CsvRow_free(&row);
	}
	List_free(&self->rows);
	free(self);
	*selfPtr = NULL;
}

CsvRow * CsvDoc_getRow(CsvDoc * self) { 
	if (self->position == -1) assert(0);
	return (CsvRow *)List_get(self->rows, self->position);
}
bool CsvDoc_moveNext(CsvDoc * self) {
	self->position++;
	return self->position < List_count(self->rows);
}
void CsvDoc_reset(CsvDoc * self) {
	self->position = -1;
}

void CsvDoc_addRow(CsvDoc * self, CsvRow * row) {
	List_add(self->rows, (void *)row);
}

const char * CsvRow_getValue(CsvRow * self) {
	if (self->position == -1) assert(0);
	return (const char *)List_get(self->values, self->position);
}

bool CsvRow_moveNext(CsvRow * self) {
	self->position++;
	return self->position < List_count(self->values);
}

void CsvRow_reset(CsvRow * self) {
	self->position = -1;
}

void CsvRow_addValue(CsvRow * self, const char * value) {
	char * strCopy = malloc(strlen(value) + 1);
	strcpy(strCopy, value);
	List_add(self->values, (void *)strCopy);
}

//

CsvDoc * CsvDoc_newFromFile(const char * filePath) { 
	char text[1000] = "";
	if (Fs_readAllText(filePath, text)) {
		CsvDoc * doc = CsvDoc_new();
		CsvRow * row = CsvRow_new();
		char ch = ' ';
		char buffer[100] = "";
		int textPos = 0;
		int pos = 0;
		do {
			ch = text[textPos++];
			if (ch == '\n' || ch == ',' || ch == '\0') {
				buffer[pos] = '\0';
				pos = 0;
				CsvRow_addValue(row, buffer);
				if (ch == '\n') {
					CsvDoc_addRow(doc, row);
					row = CsvRow_new();
				} else if (ch == '\0') {
					CsvDoc_addRow(doc, row);
				}
			} else {
				buffer[pos++] = ch;
			}
		} while (ch != '\0');
		return doc;
	}
	return NULL; 
}

void CsvDoc_writeToFile(CsvDoc * doc, const char * filePath) {
	FILE * file = fopen(filePath, "w+");
	while(CsvDoc_moveNext(doc)) {
		CsvRow * row = CsvDoc_getRow(doc);
		int i = 0;
		while(CsvRow_moveNext(row)) {
			if (i++ != 0) fprintf(file, ",");
			const char * value = CsvRow_getValue(row);
			fprintf(file, "%s", value);
		}
		fprintf(file, "\n");
	}
	fflush(file);
	fclose(file);
}