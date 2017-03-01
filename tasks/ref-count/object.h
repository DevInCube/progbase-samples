#ifndef OBJECT_H
#define OBJECT_H

typedef void (*Destructor)(void ** selfPtr);

typedef struct Object Object;
struct Object {
	Destructor destructor;
	int refCount;
};

void Object_ref(Object * self);
void Object_unref(Object * self);

/* MACROS */

#define implements(INTERFACE) \
	union {	\
		struct INTERFACE;	\
		struct INTERFACE INTERFACE;	\
	}

#endif