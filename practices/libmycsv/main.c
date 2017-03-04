#include <stdlib.h>
#include <stdio.h>

#include <csv.h>

void CsvDoc_print(CsvDoc * doc);

int main(void) {
	CsvDoc * doc = CsvDoc_newFromFile("students.csv");
	CsvDoc_print(doc);
	CsvDoc_writeToFile(doc, "out.csv");
	CsvDoc_free(&doc);
	return 0;
}

void CsvDoc_print(CsvDoc * doc) {
	CsvDoc_reset(doc);
	while(CsvDoc_moveNext(doc)) {
		CsvRow * row = CsvDoc_getRow(doc);
		CsvRow_reset(row);
		int i = 0;
		while(CsvRow_moveNext(row)) {
			if (i++ != 0) printf(", ");
			const char * value = CsvRow_getValue(row);
			printf("%s", value);
		}
		puts("");
	}
}
