#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <request.h>

static void generateRandomNumbers(Response * res, int total, int min, int max) {
	while (total-- > 0) {
		int val = rand() % (max + 1 - min) + min;
		Response_addNumber(res, val);
	}
}

void numbersHandler(Request * req, Response * res) {
	int total = rand() % 100;
	Response_setItemsType(res, RES_NUMBERS);
	generateRandomNumbers(res, total, -100, 100);
}

void bitsHandler(Request * req, Response * res) {
	int total = rand() % 32 + 1;
	Response_setItemsType(res, RES_NUMBERS);
	generateRandomNumbers(res, total, 0, 1);
}

static char * readFileContents(const char * fileName);

void stringsHandler(Request * req, Response * res) {
	const char * fileName = "./text.txt";
	char * fcontent = readFileContents(fileName);
	if (!fcontent) {
		char msg[100] = "";
		sprintf(msg, "Error: File `%s` not found", fileName);
		Response_setError(res, msg);
		return;
	}
	Response_setItemsType(res, RES_STRINGS);
	char * str = fcontent;
	const char s[2] = " ";
	char * token = strtok(str, s);
	while( token != NULL ) 
	{
		if (rand() % 2 == 0) {
			Response_addString(res, token);
		}
		token = strtok(NULL, s);
	}
	free(fcontent);
}

void strNumHandler(Request * req, Response * res) {
	const char * fileName = "./text.txt";
	char * fcontent = readFileContents(fileName);
	if (!fcontent) {
		char msg[100] = "";
		sprintf(msg, "Error: File `%s` not found", fileName);
		Response_setError(res, msg);
		return;
	}
	Response_setItemsType(res, RES_STRINGS);

	char * str = fcontent;
	const char s[2] = " ";
	char * token = strtok(str, s);
	while( token != NULL ) 
	{
		int r = rand() % 3;
		if (r == 0) {
			Response_addString(res, token);
		} else if (r == 1) {
			char numbStr[10] = "0";
			sprintf(numbStr, "%i", rand() % 200 - 100);
			Response_addString(res, numbStr);
		}
		token = strtok(NULL, s);
	}
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
