#include <stdlib.h>
#include <stdio.h>

typedef struct List List;

struct List {
	int * elements;
	int size;
	int capacity;
};

List * List_new(void);
List * List_newCapacity(int cap);

void List_free(List ** selfPtr);

void List_add(List * self, int value, int index);
int List_remove(List * self, int index);
int List_count(List * self);

int main(void) {
	List * list = List_new();
	List_add(list, 5, 2);
	printf("%i\n", List_count(list));
	List_free(&list);
	assert(list == NULL);
	return 0;
}
