#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <jansson.h>

typedef struct {
	char * name;
	char * faculty;
} Group;

typedef struct {
	char * 	name;
	char * 	surname;
	int 	year;
	float	score; 
	Group group;
} Student;

void writeJson(void) {
	Student st = {
		.name = "Taras",
		.surname = "Kartoplia",
		.year = 1990,
		.score = 4.9,
		.group = {
			.name = "KP-51",
			.faculty = "PBF",
		}
	};

	// object construction
	json_t * json = json_object();
	json_object_set_new(json, "name", json_string(st.name));
	json_object_set_new(json, "surname", json_string(st.surname));
	json_object_set_new(json, "year", json_integer(st.year));
	json_object_set_new(json, "score", json_real(st.score));
	json_t * groupObj = json_object();
	json_object_set_new(groupObj, "name", json_string(st.group.name));
	json_object_set_new(groupObj, "faculty", json_string(st.group.faculty));
	json_object_set_new(json, "group", groupObj);

	// create JSON document string
	char * jsonString = json_dumps(json, JSON_INDENT(2));
	puts(jsonString);
	free(jsonString);

    // decrease reference count (free's memory when count is 0')
	json_decref(json);
}

void readAllText(const char * filename, char * text);

void readJson(void) {
	char jsonStr[1000] = "";
	readAllText("students.json", jsonStr);

	Student students[10];
	int studentsCount = 0;

	json_error_t err;
	json_t * jsonArr = json_loads(jsonStr, 0, &err);
	int index = 0;
	json_t * value = NULL;
	json_array_foreach(jsonArr, index, value) {
		json_t * groupObj = json_object_get(value, "group");
		students[index] = (Student) {
			.name = (char *)json_string_value(json_object_get(value, "name")),
			.surname = (char *)json_string_value(json_object_get(value, "surname")),
			.year = json_integer_value(json_object_get(value, "year")),
			.score = json_real_value(json_object_get(value, "score")),
			.group = (Group) {
				.name = (char *)json_string_value(json_object_get(groupObj, "name")),
				.faculty = (char *)json_string_value(json_object_get(groupObj, "faculty"))
			}
		};
		studentsCount++;
	}

	for (int i = 0; i < studentsCount; i++) {
		Student * st = &students[i];
	    printf("\n\nStudent %i:\n", i);
		printf("\t%10s: %s\n", "name", st->name);
		printf("\t%10s: %s\n", "surname", st->surname);
		printf("\t%10s: %i\n", "year", st->year);
		printf("\t%10s: %f\n", "score", st->score);
		printf("\t%10s: %s (%s)\n", "group", 
			st->group.name, 
			st->group.faculty);
	}

	json_decref(jsonArr);
}

int main(void) {
	readJson();
	return 0;
}

void readAllText(const char * filename, char * text) {
	char line[100];
    
    FILE * fr = fopen(filename, "r");
    while(fgets(line, 100, fr)) {
        strcat(text, line);
    }
	fclose(fr);
}