#include <stdlib.h>
#include <stdio.h>
#include <list.h>
#include <assert.h>

#include <numbers.h>
#include <storage.h>

List * getNumbersOfBase(List * numbers, int base);
void freeListOfNumbers(List * list);

int main(void) {
	const char * fileIn = "myalbum.txt";
	const char * fileOut = "save.txt";
	//
	// task logic
	List * numbers = Storage_loadNumbers(fileIn);
	List * results = getNumbersOfBase(numbers, 10);
	Storage_saveResult(fileOut, results);
	//
	// free memory
	freeListOfNumbers(numbers);
	List_free(&results);  // do not use freeListOfNumbers() here as it's elements are already freed'
	return 0;
}

/**
	main task function
**/
List * getNumbersOfBase(List * numbers, int base) {
	List * result = List_new();
	int len = List_count(numbers);
	for(int i = 0; i < len; i++) {
		Number * number = List_get(numbers, i);
		if (Number_getBase(number) == base) {
			List_add(result, number);
		}
	}
	return result;
}

/**
	free list elements memory and the list itself
**/
void freeListOfNumbers(List * list) {
	int len = List_count(list);
	for(int i = 0; i < len; i++) {
		Number * number = List_get(list, i);
		Number_free(&number);
	}
	List_free(&list);
}