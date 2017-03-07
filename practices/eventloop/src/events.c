#define _XOPEN_SOURCE 700  // to enable struct timespec and clock_gettime
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <list.h>
#include <progbase.h>
#include <events.h>
#include <fs.h>
#include <time.h>

typedef struct _Clock Clock;

struct _Clock {
    struct timespec time;
};

Clock Clock_now(void);
double Clock_diffMillis(Clock c1, Clock c2);

/* Event Queue */

typedef struct EventQueue EventQueue;

EventQueue * EventQueue_new(void);
void EventQueue_free(EventQueue ** selfPtr);
void EventQueue_enqueue(EventQueue *  self, Event * event);
Event * EventQueue_dequeue(EventQueue *  self);
int EventQueue_size(EventQueue * self);

/**
	@struct EventQueue
	@brief a queue of items of type Event
*/
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

/**
	@brief adds new Event to the EventQueue tail
	@param event - new event
*/
void EventQueue_enqueue(EventQueue *  self, Event * event) {
	List_add(self->list, event);
}

/**
	@brief removes a n Event from the EventQueue head
	@returns Event from head or NULL otherwise
*/
Event * EventQueue_dequeue(EventQueue *  self) {
	Event * event = List_get(self->list, 0);
	List_removeAt(self->list, 0);
	return event;
}

/**
	@returns the number of events in EventQueue
*/
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

/**
	@brief a structure that holds information about events and handlers
*/
struct EventSystem {
	List * handlers;  /**< a list of system actors */
	EventQueue * events;  /**< a a queue of unhandled events */
};

/* EventSystem */

typedef enum {
	EventSystemActionContinue,
	EventSystemActionExit
} EventSystemAction;

/**
	@typedef HandlerObjectEnumerator
	@brief an Enumerator (Iterator) to access all handlers in EventSystem
*/
typedef struct HandlerObjectEnumerator HandlerObjectEnumerator;

bool EventSystem_handleEvent(Event * event);
Event * EventSystem_getNextEvent(void);
HandlerObjectEnumerator * EventSystem_getHandlers(void);
HandlerObject * HandlerObjectEnumerator_getNextHandler(HandlerObjectEnumerator * self);
void HandlerObjectEnumerator_free(HandlerObjectEnumerator ** selfPtr);

typedef struct EventSystem EventSystem;

static EventSystem * g_eventSystem = &(EventSystem) { NULL, NULL };

/**
	@brief a structure that holds infomation about system actors
*/
struct HandlerObject {
	void * self;  /**< a pointer to an actor data */
	Destructor destructor;  /**< a pointer to function that will be called to free self data*/
	EventHandler handler;  /**< a pointer to function that will call on self events handle */
};

void HandlerObject_handleEvent(HandlerObject * self, Event * event);
void HandlerObject_free(HandlerObject ** selfPtr);

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

void EventSystem_loop(void) {
	const int FPS = 30;
    const double millisPerFrame = 1000 / FPS;

	EventSystem_raiseEvent(Event_new(NULL, StartEventTypeId, NULL, NULL));
	double elapsedMillis = 0;
	Clock lastTicks = Clock_now();
	bool isRunning = true;
	while (isRunning) {
		Clock current = Clock_now();
        elapsedMillis = Clock_diffMillis(current, lastTicks);

		EventSystem_raiseEvent(Event_new(NULL, UpdateEventTypeId, &elapsedMillis, NULL));
		
		Event * event = NULL;
		while((event = EventSystem_getNextEvent()) != NULL) {
			HandlerObjectEnumerator * handlersEnum = EventSystem_getHandlers();
			HandlerObject * handler = NULL;
			while((handler = HandlerObjectEnumerator_getNextHandler(handlersEnum)) != NULL) {
				HandlerObject_handleEvent(handler, event);
			}
			HandlerObjectEnumerator_free(&handlersEnum);
			if (EventSystem_handleEvent(event) == EventSystemActionExit) {
				isRunning = false;
			}
			Event_free(&event);
		}

		double millis = Clock_diffMillis(Clock_now(), current);
        if (millis < millisPerFrame) sleepMillis(millisPerFrame - millis);
        lastTicks = current;
	}
}

Clock Clock_now(void) {
    Clock clock;
    clock_gettime(CLOCK_REALTIME, &(clock.time));
    return clock;
}

static double _getMillis(struct timespec * t1, struct timespec * t2) {
    double ms1 = (double)t1->tv_sec * 1000 + (double)t1->tv_nsec / 1000000.0;
    double ms2 = (double)t2->tv_sec * 1000 + (double)t2->tv_nsec / 1000000.0;
    return ms1 - ms2;
}

double Clock_diffMillis(Clock c1, Clock c2) {
    return _getMillis(&c1.time, &c2.time);
}