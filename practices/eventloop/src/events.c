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

Event * Event_new(void * sender, int type, void * data, Destructor dest) {
	Event * self = malloc(sizeof(struct Event));
	self->sender = sender;
	self->type = type;
	self->data = data;
	self->destructor = dest;
	return self;
}

void Event_free(Event ** selfPtr) {
	Event * self = *selfPtr;
	if (self->destructor != NULL && self->data != NULL) {
		self->destructor(self->data);
	}
	free(self);
	*selfPtr = NULL;
}

struct EventSystem {
	List * handlers;
	EventQueue * events;
};

static EventSystem * g_eventSystem = &(EventSystem) { NULL, NULL };

struct HandlerObject {
	void * self;
	Destructor destructor;
	EventHandler handler;
};

HandlerObject * HandlerObject_new(void * data, Destructor dest, EventHandler handler) {
	HandlerObject * self = malloc(sizeof(HandlerObject));
	self->self = data;
	self->destructor = dest;
	self->handler = handler; 
	return self;
}

void HandlerObject_free(HandlerObject ** selfPtr) {
	HandlerObject * self = *selfPtr;
	if (self->destructor != NULL && self->self != NULL) {
		self->destructor(self->self);
	}
	free(self);
	*selfPtr = NULL;
}

void HandlerObject_handleEvent(HandlerObject * self, Event * event) {
	self->handler(self->self, event);
}

static void __removeHandlerWithData(void * data);

struct HandlerObjectEnumerator {
	List * handlers;
	int index;
};

HandlerObjectEnumerator * HandlerObjectEnumerator_new(List * handlers) {
	HandlerObjectEnumerator * self = malloc(sizeof(HandlerObjectEnumerator));
	self->handlers = handlers;
	self->index = 0;
	return self;
}

void HandlerObjectEnumerator_free(HandlerObjectEnumerator ** selfPtr) {
	HandlerObjectEnumerator * self = *selfPtr;
	free(self);
	*selfPtr = NULL;
}

HandlerObject * HandlerObjectEnumerator_getNextHandler(HandlerObjectEnumerator * self) {
	if (self->index >= List_count(self->handlers)) return NULL;
	return List_get(self->handlers, self->index++);
}

Event * EventSystem_getNextEvent(void) {
	if (EventQueue_size(g_eventSystem->events) == 0) return NULL;
	return EventQueue_dequeue(g_eventSystem->events);
}

HandlerObjectEnumerator * EventSystem_getHandlers(void) {
	return HandlerObjectEnumerator_new(g_eventSystem->handlers);
}

bool EventSystem_handleEvent(Event * event) {
	if (event->type == ExitEventTypeId) {
		return EventSystemActionExit;
	}
	if (event->type == RemoveHandlerEventTypeId) {
		__removeHandlerWithData(event->data);
	}
	return EventSystemActionContinue;
}

void EventSystem_addHandler(HandlerObject * handler) {
	List_add(g_eventSystem->handlers, handler);
}

void EventSystem_removeHandler(void * handler) {
	EventSystem_raiseEvent(Event_new(NULL, RemoveHandlerEventTypeId, handler, NULL));
}

void EventSystem_raiseEvent(Event * event) {
	EventQueue_enqueue(g_eventSystem->events, event);
}

static void __removeHandlerWithData(void * data) {
	HandlerObject * handlerToRemove = NULL;	
	for (int i = 0; i < List_count(g_eventSystem->handlers); i++) {
		HandlerObject * handler = List_get(g_eventSystem->handlers, i);
		if (handler->self == data) {
			handlerToRemove = handler;
			break;
		}
	}
	if (handlerToRemove != NULL) {
		List_remove(g_eventSystem->handlers, handlerToRemove);
		HandlerObject_free(&handlerToRemove);
	}
}

void EventSystem_init(void) {
	g_eventSystem->handlers = List_new();
	g_eventSystem->events = EventQueue_new();
}

void EventSystem_deinit(void) {
	while (EventQueue_size(g_eventSystem->events) > 0) {
		Event * event = EventQueue_dequeue(g_eventSystem->events);
		Event_free(&event);
	}
	EventQueue_free(&g_eventSystem->events);
	for (int i = 0; i < List_count(g_eventSystem->handlers); i++) {
		HandlerObject * handler = List_get(g_eventSystem->handlers, i);
		HandlerObject_free(&handler);
	}
	List_free(&g_eventSystem->handlers);
}