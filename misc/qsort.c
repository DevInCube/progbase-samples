#include <stdlib.h>
#include <stdio.h>

int asc(const void * a, const void * b) {
	return *(int *)a - *(int *)b;
}

int desc(const void * a, const void * b) {
	return *(int *)b - *(int *)a;
}

void printArr(int * arr, int count);

int main(void) {
	int arr[] = {5, 0, -4, 4, 5, 10};
	int length = sizeof(arr) / sizeof (arr[0]);

	printf("Array: ");
	printArr(arr, length);
	
	printf("Ascending: ");
	qsort(arr, length, sizeof(arr[0]), asc);
	printArr(arr, length);

	printf("Descending: ");
	qsort(arr, length, sizeof(arr[0]), desc);
	printArr(arr, length);

	return 0;
}

void printArr(int * arr, int count) {
	for (int i = 0; i < count; i++) {
		printf("%i ", arr[i]);
	}
	puts("");
}
