#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <list.h>
#include <events.h>
#include <progbase.h>
#include <pbconsole.h>

typedef struct KeyInputEvent KeyInputEvent;
struct KeyInputEvent {
	char keyCode; 
};
enum { KeyInputEventTypeId = 47578 };

Event * KeyInputEvent_new(void * sender, char key) {
	KeyInputEvent * data = malloc(sizeof(struct KeyInputEvent));
	data->keyCode = key;
	return Event_new(sender, KeyInputEventTypeId, data, free);
}

typedef struct RandomNumberEvent RandomNumberEvent;
struct RandomNumberEvent {
	int number;
};
enum { RandomNumberEventTypeId = 134134 };

Event * RandomNumberEvent_new(void * sender, int number) {
	RandomNumberEvent * data = malloc(sizeof(struct RandomNumberEvent));
	data->number = number;
	return Event_new(sender, RandomNumberEventTypeId, data, free);
}

void RandomEventGen_update(void * self, Event * event);
void InputManager_update(void * self, Event * event);
void CustomHandler_handleEvent(void * self, Event * event);
void Timer_handleEvent(void * self, Event * event);

enum { 
	ExitEventTypeId = -1,
	UpdateEventTypeId = 0,
	StartEventTypeId = 1,
	RemoveHandlerEventTypeId = 767456
};

typedef struct HandlerObject HandlerObject;
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

typedef struct EventSystem EventSystem;
struct EventSystem {
	List * handlers;
	EventQueue * events;
};

typedef enum {
	EventSystemActionContinue,
	EventSystemActionExit
} EventSystemAction;

EventSystem * g_eventSystem = NULL;

typedef struct HandlerObjectEnumerator HandlerObjectEnumerator;

void EventSystem_addHandler(HandlerObject * handler);
void EventSystem_removeHandler(void * handler);
void EventSystem_raiseEvent(Event * event);
Event * EventSystem_getNextEvent(void);
HandlerObjectEnumerator * EventSystem_getHandlers(void);
bool EventSystem_handleEvent(Event * event);

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

int main(void) {
	g_eventSystem = &(EventSystem) { 
		.handlers = List_new(), 
		.events = EventQueue_new()
	};

	List_add(g_eventSystem->handlers, HandlerObject_new(NULL, NULL, RandomEventGen_update));
	List_add(g_eventSystem->handlers, HandlerObject_new(NULL, NULL, InputManager_update));
	int spaceHitCounter = 0;
	List_add(g_eventSystem->handlers, HandlerObject_new(&spaceHitCounter, NULL, CustomHandler_handleEvent));
	int timeCounter = 100;
	List_add(g_eventSystem->handlers, HandlerObject_new(&timeCounter, NULL, Timer_handleEvent));

	EventSystem_raiseEvent(Event_new(NULL, StartEventTypeId, NULL, NULL));
	bool isRunning = true;
	while (isRunning) {
		EventSystem_raiseEvent(Event_new(NULL, UpdateEventTypeId, NULL, NULL));
		
		Event * event = NULL;
		while((event = EventSystem_getNextEvent()) != NULL) {
			HandlerObjectEnumerator * handlersEnum = EventSystem_getHandlers();
			HandlerObject * handler = NULL;
			while((handler = HandlerObjectEnumerator_getNextHandler(handlersEnum)) != NULL) {
				handler->handler(handler->self, event);
			}
			HandlerObjectEnumerator_free(&handlersEnum);
			if (EventSystem_handleEvent(event) == EventSystemActionExit) {
				isRunning = false;
			}
			Event_free(&event);
		}
		sleepMillis(33);  // ~ 30 FPS
	}
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
	return 0;
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

void RandomEventGen_update(void * self, Event * event) {
	if (event->type == StartEventTypeId) {
		srand(time(0));
	}
	if (rand() % 33 == 0) {
		int number = rand() % 200 - 100;
		EventSystem_raiseEvent(RandomNumberEvent_new(self, number));
	}
}

void InputManager_update(void * self, Event * event) {
	if (conIsKeyDown()) {
		char keyCode = getchar();
		EventSystem_raiseEvent(KeyInputEvent_new(self, keyCode));
	}
}

enum { CustomEventTypeId = 124090 };

void CustomHandler_handleEvent(void * self, Event * event) {
	switch (event->type) {
		case StartEventTypeId: {
			puts("START!");
			break;
		}
		case UpdateEventTypeId: {
			putchar('.');
			break;
		}
		case RandomNumberEventTypeId: {
			RandomNumberEvent * randEvent = (RandomNumberEvent *)event->data;
			printf("Random number %i\n", randEvent->number);
			break;
		}
		case KeyInputEventTypeId: {
			KeyInputEvent * keyEvent = (KeyInputEvent *)event->data;
			if (keyEvent->keyCode == ' ') {
				EventSystem_raiseEvent(Event_new(self, CustomEventTypeId, NULL, NULL));
			}
			if (keyEvent->keyCode == 'a') {
				int * timer = malloc(sizeof(int));
				*timer = 50;
				HandlerObject * handler = malloc(sizeof(HandlerObject));
				handler->self = timer;
				handler->handler = Timer_handleEvent;
				handler->destructor = free;
				EventSystem_addHandler(handler);
			}
			if (keyEvent->keyCode == 'q') {
				EventSystem_raiseEvent(Event_new(self, ExitEventTypeId, NULL, NULL));
			}
			printf("Key pressed `%c` [%i]\n", 
				keyEvent->keyCode, keyEvent->keyCode);
			break;
		}
		case CustomEventTypeId: {
			int * counterPtr = (int *)self;
			(*counterPtr)++;
			printf(">>> Custom event! Counter: %i\n", *counterPtr);
			break;
		}
	} 
}

void Timer_handleEvent(void * self, Event * event) {
	switch(event->type) {
		case UpdateEventTypeId: {
			int * timePtr = (int *)self;
			*timePtr -= 1;
			if (*timePtr % 10 == 0) {
				printf("\nTimer: %i\n", *timePtr); 
			}
			if (*timePtr == 0) {
				printf("\nTimer COMPLETED!\n"); 
				EventQueue_enqueue(
					g_eventSystem->events, 
					Event_new(self, RemoveHandlerEventTypeId, self, NULL));
			}
			break;
		}
	}
}