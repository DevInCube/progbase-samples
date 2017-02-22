#include <int_list.h>
#include <assert.h>

void print(IntList * list) {
	for (int i = 0; i < IntList_count(list); i++) {
		int value = IntList_get(list, i);
		printf("%i ", value);
	}
}

int main(void) {
	IntList * gdkLabScores = IntList_new();
	IntList * opLabScores = IntList_new();

	IntList_add(gdkLabScores, 5);
	IntList_add(gdkLabScores, 7);
	IntList_insert(gdkLabScores, 1, 6);
	assert(IntList_get(gdkLabScores, 0) == 5);
	assert(IntList_get(gdkLabScores, 1) == 6);
	assert(IntList_get(gdkLabScores, 2) == 7);
	assert(IntList_count(gdkLabScores) == 3);
	assert(IntList_count(opLabScores) == 0);

	print(gdkLabScores);

	IntList_clear(gdkLabScores);
	assert(IntList_count(gdkLabScores) == 0);

	IntList_free(&gdkLabScores);
	assert(gdkLabScores == NULL);
	IntList_free(&opLabScores);
	return 0;
}