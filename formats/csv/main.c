#include <stdlib.h>
#include <stdio.h>
#include <csv.h>

struct Student {
	char name[100];
	float score;
};

int main(void) {
	struct Student students[2] = {
		{"Vasya", 4.5},
		{"Inna", 3.6}
	};
	char buffer[1000] = "";
	int test = csv_write(buffer, 1000, students, sizeof(students));
	printf("Test %i\n%s\n\n", test, buffer);
	return 0;
}
