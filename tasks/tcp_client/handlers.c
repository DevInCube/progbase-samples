#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <jansson.h>

#include <request.h>

static void generateRandomNumbersJson(NetMessage * message, int total, int min, int max) {
	json_t * jarray = json_array();
	while (total-- > 0) {
		int val = rand() % (max + 1 - min) + min;
		json_array_append(jarray, json_integer(val));
	}
	const char * str = json_dumps(jarray, JSON_COMPACT);
	NetMessage_setDataString(message, str);
	free((void *)str);
	json_decref(jarray);
}

void numbersHandler(Request * req, NetMessage * message) {
	int total = rand() % 100;
	generateRandomNumbersJson(message, total, -100, 100);
}

void bitsHandler(Request * req, NetMessage * message) {
	int total = rand() % 32 + 1;
	generateRandomNumbersJson(message, total, 0, 1);
}

static char * readFileContents(const char * fileName);

void stringsHandler(Request * req, NetMessage * message) {
	const char * fileName = "./text.txt";
	char * fcontent = readFileContents(fileName);
	if (!fcontent) {
		char msg[100] = "";
		sprintf(msg, "Error: File `%s` not found", fileName);
		NetMessage_setDataString(message, msg);
		return;
	}

	json_t * jarray = json_array();

	char * str = fcontent;
	const char s[2] = " ";
	char * token = strtok(str, s);
	while( token != NULL ) 
	{
		if (rand() % 2 == 0) {
			json_array_append(jarray, json_string(token));
		}
		token = strtok(NULL, s);
	}

	const char * strDump = json_dumps(jarray, JSON_COMPACT);
	NetMessage_setDataString(message, strDump);
	free((void *)strDump);
	json_decref(jarray);

	free(fcontent);
}

void strNumHandler(Request * req, NetMessage * message) {
	const char * fileName = "./text.txt";
	char * fcontent = readFileContents(fileName);
	if (!fcontent) {
		char msg[100] = "";
		sprintf(msg, "Error: File `%s` not found", fileName);
		NetMessage_setDataString(message, msg);
		return;
	}

	json_t * jarray = json_array();

	char * str = fcontent;
	const char s[2] = " ";
	char * token = strtok(str, s);
	while( token != NULL ) 
	{
		int r = rand() % 3;
		if (r == 0) {
			json_array_append(jarray, json_string(token));
		} else if (r == 1) {
			char numbStr[10] = "0";
			sprintf(numbStr, "%i", rand() % 200 - 100);
			json_array_append(jarray, json_string(numbStr));
		}
		token = strtok(NULL, s);
	}

	const char * strDump = json_dumps(jarray, JSON_COMPACT);
	NetMessage_setDataString(message, strDump);
	free((void *)strDump);
	json_decref(jarray);

	free(fcontent);
}

//

static char * readFileContents(const char * fileName) {
	FILE * textFile = fopen(fileName, "r");
	if (textFile == NULL) {
		return NULL;
	}
	fseek(textFile, 0, SEEK_END); 
	long size = ftell(textFile);
	fseek(textFile, 0, SEEK_SET); 
	char * fcontent = malloc(size);
	fread(fcontent, 1, size, textFile);
	fclose(textFile);
	return fcontent;
}
