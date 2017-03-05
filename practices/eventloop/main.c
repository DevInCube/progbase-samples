#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <events.h>
#include <progbase.h>
#include <pbconsole.h>

typedef void (*EventHandler)(Event * event, EventQueue * events);

typedef struct KeyInputEvent KeyInputEvent;
struct KeyInputEvent {
	struct { Event; };  // -Wno-microsoft to disable this error
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

void RandomNumberEvent_free(RandomNumberEvent ** selfPtr) {
	free(*selfPtr);
	*selfPtr = NULL;
}

void RandomEventGen_update(Event * event, EventQueue * events);
void InputManager_update(Event * event, EventQueue * events);
void Event_handleEvent(Event * event, EventQueue * events);

enum { UpdateEventTypeId = 0 };

int main(void) {
	srand(time(NULL));

	EventHandler handlers[] = {
		RandomEventGen_update,
		InputManager_update,
		Event_handleEvent
	};
	int handlersLength = sizeof(handlers) / sizeof(handlers[0]);
	
	EventQueue * eventList = EventQueue_new();
	while (1) {
		Event * updateEvent = Event_new(UpdateEventTypeId, NULL);
		EventQueue_enqueue(eventList, updateEvent);
		while (EventQueue_size(eventList) > 0) {
			Event * event = EventQueue_dequeue(eventList);
			for (int i = 0; i < handlersLength; i++) {
				handlers[i](event, eventList);
			}
			Event_free(&event);
		}
		sleepMillis(33);  // ~ 30 FPS
	}
	EventQueue_free(&eventList);
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