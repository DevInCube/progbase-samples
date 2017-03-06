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

int main(void) {
	EventSystem_init();

	EventSystem_addHandler(HandlerObject_new(NULL, NULL, RandomEventGen_update));
	EventSystem_addHandler(HandlerObject_new(NULL, NULL, InputManager_update));
	int spaceHitCounter = 0;
	EventSystem_addHandler(HandlerObject_new(&spaceHitCounter, NULL, CustomHandler_handleEvent));
	int timeCounter = 100;
	EventSystem_addHandler(HandlerObject_new(&timeCounter, NULL, Timer_handleEvent));

	EventSystem_raiseEvent(Event_new(NULL, StartEventTypeId, NULL, NULL));
	bool isRunning = true;
	while (isRunning) {
		EventSystem_raiseEvent(Event_new(NULL, UpdateEventTypeId, NULL, NULL));
		
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
		sleepMillis(33);  // ~ 30 FPS
	}
	EventSystem_deinit();
	return 0;
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
				EventSystem_addHandler(HandlerObject_new(timer, free, Timer_handleEvent));
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
				EventSystem_raiseEvent(Event_new(self, RemoveHandlerEventTypeId, self, NULL));
			}
			break;
		}
	}
}