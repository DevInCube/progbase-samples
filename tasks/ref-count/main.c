/**
	The task is to read numbers with different bases from text file,
	store them as a Sequence of numbers,
	filter only decimal numbers into new sequence and save it to another file
**/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <numbers.h>
#include <storage.h>

Sequence * getNumbersOfBase(Sequence * numbers, int base);
void freeSequenceOfNumbers(Sequence * list);

int main(void) {
	const char * fileIn = "myalbum.txt";
	const char * fileOut = "save.txt";
	//
	// task logic
	Sequence * numbers = Storage_loadNumbers(fileIn);
	Sequence * results = getNumbersOfBase(numbers, 10);
	Storage_saveResult(fileOut, results);
	//
	// free memory
	freeSequenceOfNumbers(numbers);
	Sequence_free(&results);  // do not use freeSequenceOfNumbers() here as it's elements are already freed'
	return 0;
}

/**
	main task function
**/
Sequence * getNumbersOfBase(Sequence * numbers, int base) {
	Sequence * result = Sequence_new();
	int len = Sequence_count(numbers);
	for(int i = 0; i < len; i++) {
		Number * number = Sequence_get(numbers, i);
		if (Number_getBase(number) == base) {
			Sequence_add(result, number);
		}
	}
	return result;
}

/**
	free list elements memory and the list itself
**/
void freeSequenceOfNumbers(Sequence * list) {
	int len = Sequence_count(list);
	for(int i = 0; i < len; i++) {
		Number * number = Sequence_get(list, i);
		Number_free(&number);
	}
	Sequence_free(&list);
}