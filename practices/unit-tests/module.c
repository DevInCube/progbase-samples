#include <module.h>
#include <errno.h>

int Module_min(List * list) {
	int length = List_count(list);
	if (length == 0) {
		errno = MODULE_ERR_LIST_EMPTY;
		return 0;
	}
	int minimum = *(int *)List_get(list, 0);
	for(int i = 1; i < length; i++) {
		int value = *(int *)List_get(list, i);
		if (value < minimum) {
			minimum = value;
		}
	}
	return minimum;
}
