#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <fs.h>

bool Fs_readAllText(const char * filename, char * text) {
	char line[100];
    
    FILE * fr = fopen(filename, "r");
	if (fr == NULL) return false;
    while(fgets(line, 100, fr)) {
        strcat(text, line);
    }
	fclose(fr);
	return true;
}