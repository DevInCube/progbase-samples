#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <list.h>

#include <events.h>
#include <fs.h>

struct EventQueue {
	List * list;
};

EventQueue * EventQueue_new(void) {
	EventQueue * self = malloc(sizeof(EventQueue));
	self->list = List_new();
	return self;
}

void EventQueue_free(EventQueue ** selfPtr) {
	EventQueue * self = *selfPtr;
	List_free(&self->list);
	free(self);
	*selfPtr = NULL;
}

void EventQueue_enqueue(EventQueue *  self, Event * event) {
	List_add(self->list, event);
}
Event * EventQueue_dequeue(EventQueue *  self) {
	Event * event = List_get(self->list, 0);
	List_removeAt(self->list, 0);
	return event;
}
int EventQueue_size(EventQueue * self) {
	return List_count(self->list);
}


Event * Event_new(void * sender, int type, Destructor dest, void * data) {
	Event * self = malloc(sizeof(struct Event));
	self->sender = sender;
	self->type = type;
	self->destructor = dest;
	self->data = data;
	return self;
}

void Event_free(Event ** selfPtr) {
	Event * self = *selfPtr;
	if (self->destructor != NULL) {
		self->destructor(self->data);
	} else {
		free(self->data);
	}
	free(self);
	*selfPtr = NULL;
}