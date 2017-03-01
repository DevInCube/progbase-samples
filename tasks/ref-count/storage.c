#include <storage.h>
#include <numbers.h>

#include <stdio.h>

static void __printSequenceOfNumbers(Sequence * list);

Sequence * Storage_loadNumbers(const char * fileName) {
	/* this is a fake function implementation */
	Sequence * list = Sequence_new();
	Sequence_add(list, Number_new(13, 10));
	Sequence_add(list, Number_new(6, 8));
	Sequence_add(list, Number_new(144, 10));
	Sequence_add(list, Number_new(14, 2));
	Sequence_add(list, Number_new(0, 10));
	printf("%s(%s):\n", __func__, fileName);
	__printSequenceOfNumbers(list);
	return list;
}

void Storage_saveResult(const char * fileName, Sequence * result) {
	/* this is a fake function implementation */
	printf("%s(%s):\n", __func__, fileName);
	__printSequenceOfNumbers(result);
}

/**
	private function for test console output 
*/
static void __printSequenceOfNumbers(Sequence * list) {
	int len = Sequence_count(list);
	char buffer[100] = "";
	for(int i = 0; i < len; i++) {
		Number * number = Sequence_get(list, i);
		printf("%s, ", Number_toString(number, buffer));
	}
	puts("");
}