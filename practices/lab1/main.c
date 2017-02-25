#include <stdlib.h>
#include <stdio.h>
#include <list.h>
#include <assert.h>

#include <convert.h>
#include <storage.h>

void List_print(List * list) {
	int len = List_count(list);
	for(int i = 0; i < len; i++) {
		void * value = List_get(list, i);
		int intValue = *(int *)value;
		printf("%i ", intValue);
	}
}

int main(void) {

	int error = 1;
	if (error) throw("Some error occured");

	const char * fileName = "myalbum.txt";
	List * compositions = Storage_load(fileName);

	for (int i = 0; i < List_count(compositions); i++) {
		Composition_print(List_get(compositions, i));
	}

	Storage_save("album2.txt", compositions);

	
	for (int i = 0; i < List_count(compositions); i++) {
		Composition * composition = 
			(Composition *)List_get(compositions, i);
		Composition_free(&composition);
	}
	List_free(&compositions);

	puts("");
	return 0;
}
