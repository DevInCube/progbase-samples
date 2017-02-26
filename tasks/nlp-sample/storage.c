#include <storage.h>
#include <numbers.h>

#include <stdio.h>

static void __printListOfNumbers(List * list);

List * Storage_loadNumbers(const char * fileName) {
	/* this is a fake function implementation */
	List * list = List_new();
	List_add(list, Number_new(13, 10));
	List_add(list, Number_new(6, 8));
	List_add(list, Number_new(144, 10));
	List_add(list, Number_new(14, 2));
	List_add(list, Number_new(0, 10));
	printf("%s(%s):\n", __func__, fileName);
	__printListOfNumbers(list);
	return list;
}

void Storage_saveResult(const char * fileName, List * result) {
	/* this is a fake function implementation */
	printf("%s(%s):\n", __func__, fileName);
	__printListOfNumbers(result);
}

/**
	private function for test console output 
*/
static void __printListOfNumbers(List * list) {
	int len = List_count(list);
	char buffer[100] = "";
	for(int i = 0; i < len; i++) {
		Number * number = List_get(list, i);
		printf("%s", Number_toString(number, buffer));
	}
	puts("");
}