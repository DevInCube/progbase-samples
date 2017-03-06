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
	return Event_new(sender, KeyInputEventTypeId, NULL, data);
}

typedef struct RandomNumberEvent RandomNumberEvent;
struct RandomNumberEvent {
	int number;
};
enum { RandomNumberEventTypeId = 134134 };

Event * RandomNumberEvent_new(void * sender, int number) {
	RandomNumberEvent * data = malloc(sizeof(struct RandomNumberEvent));
	data->number = number;
	return Event_new(sender, RandomNumberEventTypeId, NULL, data);
}

void RandomEventGen_update(void * self, Event * event, EventQueue * events);
void InputManager_update(void * self, Event * event, EventQueue * events);
void Event_handleEvent(void * self, Event * event, EventQueue * events);

enum { 
	UpdateEventTypeId = 0,
	StartEventTypeId = 1
};

typedef struct HandlerObject HandlerObject;
struct HandlerObject {
	void * self;
	EventHandler handler;
};

int main(void) {
	List * handlers = List_new();
	List_add(handlers, &(HandlerObject){NULL, RandomEventGen_update});
	List_add(handlers, &(HandlerObject){NULL, InputManager_update});
	int counter = 0;
	List_add(handlers, &(HandlerObject){&counter, Event_handleEvent});	
	
	EventQueue * eventList = EventQueue_new();
	int started = 0;
	while (1) {
		if (!started) {
			started = 1;
			EventQueue_enqueue(eventList, Event_new(NULL, StartEventTypeId, NULL, NULL));
		}
		EventQueue_enqueue(eventList, Event_new(NULL, UpdateEventTypeId, NULL, NULL));
		while (EventQueue_size(eventList) > 0) {
			Event * event = EventQueue_dequeue(eventList);
			for (int i = 0; i < List_count(handlers); i++) {
				HandlerObject * handler = List_get(handlers, i);
				handler->handler(handler->self, event, eventList);
			}
			Event_free(&event);
		}
		sleepMillis(33);  // ~ 30 FPS
	}
	EventQueue_free(&eventList);
	List_free(&handlers);
	return 0;
}

void RandomEventGen_update(void * self, Event * event, EventQueue * events) {
	if (event->type == StartEventTypeId) {
		srand(time(0));
	}
	if (rand() % 33 == 0) {
		int number = rand() % 200 - 100;
		EventQueue_enqueue(
			events, 
			RandomNumberEvent_new(self, number));
	}
}

void InputManager_update(void * self, Event * event, EventQueue * events) {
	if (conIsKeyDown()) {
		char ch = getchar();
		EventQueue_enqueue(
			events, 
			(Event *)KeyInputEvent_new(self, ch));
	}
}

enum { CustomEventTypeId = 124090 };

void Event_handleEvent(void * self, Event * event, EventQueue * eventList) {
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
				EventQueue_enqueue(
					eventList, 
					Event_new(self, CustomEventTypeId, NULL, NULL));
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