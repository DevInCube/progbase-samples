#ifndef MODULE_H
#define MODULE_H

typedef struct Event Event;

typedef struct EventQueue EventQueue;

EventQueue * EventQueue_new(void);
void EventQueue_free(EventQueue ** selfPtr);
void EventQueue_enqueue(EventQueue *  self, Event * event);
Event * EventQueue_dequeue(EventQueue *  self);
int EventQueue_size(EventQueue * self);

typedef void (*Destructor)(Event ** event);

struct Event {
	Destructor destructor;
	int type;
};

Event * Event_new(int eventType, Destructor dest);
void Event_free(Event ** selfPtr);

typedef void (*EventHandler)(void * self, Event * event, EventQueue * events);

#define extends(SUPERTYPE) \
	struct { \
		struct SUPERTYPE; \
		struct SUPERTYPE SUPERTYPE; \
	}

#define if_let(VARIN, TYPE, VAROUT) \
	for (TYPE * VAROUT = (TYPE *)VARIN; \
		VARIN->type == TYPE##TypeId;)

#endif
