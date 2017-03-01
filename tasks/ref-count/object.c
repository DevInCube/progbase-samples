#include <object.h>

void Object_ref(Object * self) {
	self->refCount++;
}

void Object_unref(Object * self) {
	self->refCount--;
	if (self->refCount == 0 && self->destructor) {
		self->destructor((void **)&self);
	}
}
