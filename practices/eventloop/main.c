#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <list.h>
#include <events.h>
#include <progbase.h>
#include <pbconsole.h>

typedef struct KeyInputEvent KeyInputEvent;
struct KeyInputEvent {
	struct { Event; };
	char keyCode; 
};
enum { KeyInputEventTypeId = 47578 };

KeyInputEvent * KeyInputEvent_new(char key) {
	KeyInputEvent * self = malloc(sizeof(struct KeyInputEvent));
	self->destructor = NULL;
	self->type = KeyInputEventTypeId;
	self->keyCode = key;
	return self;
}

typedef struct RandomNumberEvent RandomNumberEvent;
struct RandomNumberEvent {
	struct { Event; };
	int number;
};
enum { RandomNumberEventTypeId = 134134 };

RandomNumberEvent * RandomNumberEvent_new(int number) {
	RandomNumberEvent * self = malloc(sizeof(struct RandomNumberEvent));
	self->destructor = NULL;
	self->type = RandomNumberEventTypeId;
	self->number = number;
	return self;
}

void RandomEventGen_update(Event * event, EventQueue * events);
void InputManager_update(Event * event, EventQueue * events);
void Event_handleEvent(Event * event, EventQueue * events);

enum { UpdateEventTypeId = 0 };

int main(void) {
	srand(time(NULL));

	List * handlers = List_new();
	List_add(handlers, RandomEventGen_update);
	List_add(handlers, InputManager_update);
	List_add(handlers, Event_handleEvent);	
	
	EventQueue * eventList = EventQueue_new();
	while (1) {
		Event * updateEvent = Event_new(UpdateEventTypeId, NULL);
		EventQueue_enqueue(eventList, updateEvent);
		while (EventQueue_size(eventList) > 0) {
			Event * event = EventQueue_dequeue(eventList);
			for (int i = 0; i < List_count(handlers); i++) {
				EventHandler handler = List_get(handlers, i);
				handler(event, eventList);
			}
			Event_free(&event);
		}
		sleepMillis(33);  // ~ 30 FPS
	}
	EventQueue_free(&eventList);
	List_free(&handlers);
	return 0;
}

void RandomEventGen_update(Event * event, EventQueue * events) {
	if (rand() % 33 == 0) {
		int number = rand() % 200 - 100;
		EventQueue_enqueue(
			events, 
			(Event *)RandomNumberEvent_new(number));
	}
}

void InputManager_update(Event * event, EventQueue * events) {
	if (conIsKeyDown()) {
		char ch = getchar();
		EventQueue_enqueue(
			events, 
			(Event *)KeyInputEvent_new(ch));
	}
}

enum { CustomEventTypeId = 124090 };

void Event_handleEvent(Event * event, EventQueue * eventList) {
	switch (event->type) {
		case UpdateEventTypeId: {
			putchar('.');
			break;
		}
		case RandomNumberEventTypeId: {
			RandomNumberEvent * randEvent = (RandomNumberEvent *)event;
			printf("Random number %i\n", randEvent->number);
			break;
		}
		case KeyInputEventTypeId: {
			KeyInputEvent * keyEvent = (KeyInputEvent *)event;
			if (keyEvent->keyCode == ' ') {
				EventQueue_enqueue(
					eventList, 
					Event_new(CustomEventTypeId, NULL));
			}
			printf("Key pressed `%c` [%i]\n", 
				keyEvent->keyCode, keyEvent->keyCode);
			break;
		}
		case CustomEventTypeId: {
			printf(">>> Custom event!\n");
			break;
		}
	} 
}