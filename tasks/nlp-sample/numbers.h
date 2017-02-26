#ifndef NUMBERS_H
#define NUMBERS_H

/**
	a type for number with a base 
*/
typedef struct Number Number;

/* constructors */
Number * Number_new(int value, int base);
Number * Number_newFromString(const char * str);
/* destructor */
void Number_free(Number ** selfPtr);
/* getter methods */
int Number_getValue(Number * self);
int Number_getBase(Number * self);
/* convertion method */
char * Number_toString(Number * self, char * buffer);

#endif