#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <list.h>
#include <events.h>
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

typedef struct Timer Timer;
struct Timer {
	int id;
	int timeCounter;
};

int main(void) {
	EventSystem_init();

	// add event handlers
	EventSystem_addHandler(HandlerObject_new(NULL, NULL, RandomEventGen_update));
	EventSystem_addHandler(HandlerObject_new(NULL, NULL, InputManager_update));
	Timer timer = {
		.id = 0,
		.timeCounter = 100
	};
	EventSystem_addHandler(HandlerObject_new(&timer, NULL, Timer_handleEvent));
	int spaceHitCounter = 0;
	EventSystem_addHandler(HandlerObject_new(&spaceHitCounter, NULL, CustomHandler_handleEvent));

	// start infinite event loop
	EventSystem_loop();
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
				Timer * timer = malloc(sizeof(Timer));
				timer->id = rand() % 100;
				timer->timeCounter = 50;
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
			Timer * timer = (Timer *)self;
			double elapsedMillis = *(double *)event->data;
			timer->timeCounter -= 1;
			if (timer->timeCounter % 10 == 0) {
				printf("\nTimer [%i]: %i {%lf}\n", timer->id, timer->timeCounter, elapsedMillis); 
			}
			if (timer->timeCounter == 0) {
				printf("\nTimer [%i] COMPLETED!\n", timer->id); 
				EventSystem_raiseEvent(Event_new(self, RemoveHandlerEventTypeId, self, NULL));
			}
			break;
		}
	}
}