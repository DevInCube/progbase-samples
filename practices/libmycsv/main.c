#include <stdlib.h>
#include <stdio.h>

#include <csv.h>

int main(void) {
	CsvDoc * doc = CsvDoc_newFromFile("students.csv");
	// while(CsvDoc_moveNext(doc)) {
	// 	CsvRow * row = CsvDoc_getRow(doc);
	// 	while(CsvRow_moveNext(row)) {
	// 		const char * value = CsvRow_getValue(row);
	// 		printf("%s, ", value);
	// 	}
	// 	puts("");
	// }
	// puts("END");
	CsvDoc_writeToFile(doc, "out.csv");
	CsvDoc_free(&doc);
	return 0;
}
