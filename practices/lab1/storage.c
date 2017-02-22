#include <storage.h>

#include <stdio.h>

List * Storage_load(const char * fileName) {
	List * list = List_new();
	List_add(list, Composition_newFromString("Muse;SMBH;230."));
	List_add(list, Composition_newFromString("Radiohead;Nude;313."));
	return list;
}

void Storage_save(const char * fileName, List * compositions) {
	printf("List saved to %s\n", fileName);
	char buffer[100];
	for (int i = 0; i < List_count(compositions); i++) {
		Composition * c = (Composition *)List_get(compositions, i);
		char * strPtr = Composition_toString(c, buffer);
		printf("\t%i) %s\n", i, strPtr);
	}
}
