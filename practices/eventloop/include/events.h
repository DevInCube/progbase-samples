#ifndef MODULE_H
#define MODULE_H

typedef struct Event Event;

typedef struct EventQueue EventQueue;

EventQueue * EventQueue_new(void);
void EventQueue_free(EventQueue ** selfPtr);
void EventQueue_enqueue(EventQueue *  self, Event * event);
Event * EventQueue_dequeue(EventQueue *  self);
int EventQueue_size(EventQueue * self);

typedef void (*Destructor)(void * dataPtr);

struct Event {
	void * sender;
	int type;
	void * data;
	Destructor destructor;
};

Event * Event_new(void * sender, int type, void * data, Destructor dest);
void Event_free(Event ** selfPtr);

typedef void (*EventHandler)(void * self, Event * event);

typedef struct HandlerObject HandlerObject;

HandlerObject * HandlerObject_new(void * data, Destructor dest, EventHandler handler);
void HandlerObject_free(HandlerObject ** selfPtr);
void HandlerObject_handleEvent(HandlerObject * self, Event * event);

typedef struct EventSystem EventSystem;

typedef enum {
	EventSystemActionContinue,
	EventSystemActionExit
} EventSystemAction;

typedef struct HandlerObjectEnumerator HandlerObjectEnumerator;

void EventSystem_init(void);
void EventSystem_deinit(void);
void EventSystem_loop(void);
void EventSystem_addHandler(HandlerObject * handler);
void EventSystem_removeHandler(void * handler);
void EventSystem_raiseEvent(Event * event);
bool EventSystem_handleEvent(Event * event);
Event * EventSystem_getNextEvent(void);
HandlerObjectEnumerator * EventSystem_getHandlers(void);
HandlerObject * HandlerObjectEnumerator_getNextHandler(HandlerObjectEnumerator * self);
void HandlerObjectEnumerator_free(HandlerObjectEnumerator ** selfPtr);

enum { 
	ExitEventTypeId = -1,
	UpdateEventTypeId = 0,
	StartEventTypeId = 1,
	RemoveHandlerEventTypeId = 767456
};

#endif
