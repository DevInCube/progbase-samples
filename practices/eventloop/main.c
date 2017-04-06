#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <list.h>
#include <events.h>
#include <pbconsole.h>
#include <progbase.h>

/* custom constant event type ids*/
enum {
	KeyInputEventTypeId,
	TimerElapsedEventTypeId
};

/* event handler functions prototypes */
void KeyInputHandler_update(EventHandler * self, Event * event);
void KeyInputListener_update(EventHandler * self, Event * event);

typedef struct Timer {
	double totalMillis;
	double elapsedMillis;
} Timer;

Timer * Timer_new(double millis) {
	Timer * self = malloc(sizeof(Timer));
	self->totalMillis = millis;
	self->elapsedMillis = 0;
	return self;
}

void Timer_free(Timer * self) {
	free(self);
}

void Timer_handleEvent(EventHandler * self, Event * event) {
	// @todo
	Timer * timer = (Timer *)self->data;
	switch(event->type) {
		case UpdateEventTypeId: {
			double elapsed = *(double *)event->data;
			timer->elapsedMillis += elapsed;
			printf("%.2lf/%.2lf (%.2lf)\n", timer->elapsedMillis, timer->totalMillis, elapsed);
			fflush(stdout);
			if (timer->elapsedMillis > timer->totalMillis) {
				double * elapsedPtr = malloc(sizeof(double));
				*elapsedPtr = timer->elapsedMillis;
				//printf(">>> TIMER ELAPSED!!!!\n");
				EventSystem_emit(Event_new(
					self, 
					TimerElapsedEventTypeId, 
					elapsedPtr,
					free));

				timer->elapsedMillis = 0;
			}
			sleepMillis(250);
			break;
		}
		default: {
			break;
		}
	}
}

void Printer_handleEvent(EventHandler * self, Event * event) {
	if (event->type == TimerElapsedEventTypeId) {
		double elapsed = *(double *)event->data;
		printf(">>> TIMER ELAPSED [%.2lf]!!!!\n", elapsed);
	}
}

int main(void) {
	// startup event system
	EventSystem_init();

	// add event handlers
	// EventSystem_addHandler(EventHandler_new(NULL, NULL, KeyInputHandler_update));
	// EventSystem_addHandler(EventHandler_new(NULL, NULL, KeyInputListener_update));

	EventSystem_addHandler(EventHandler_new(NULL, NULL, Printer_handleEvent));

	EventSystem_addHandler(EventHandler_new(
		Timer_new(3000), 
		(DestructorFunction)Timer_free, 
		Timer_handleEvent));

	// start infinite event loop
	EventSystem_loop();
	// cleanup event system
	EventSystem_cleanup();
	return 0;
}

/* event handlers functions implementations */

void KeyInputHandler_update(EventHandler * self, Event * event) {
	if (conIsKeyDown()) {  // non-blocking key input check
        char keyCode = getchar(); 
		if (keyCode == 27) {  // Escape key code
			EventSystem_exit();	
		} else {
            char * keyCodeData = malloc(sizeof(char));
		    *keyCodeData = keyCode;
			EventSystem_emit(Event_new(self, KeyInputEventTypeId, keyCodeData, free));
		}
	}
}

void KeyInputListener_update(EventHandler * self, Event * event) {
	switch(event->type) {
		case StartEventTypeId: {
			puts("Press [Esc] to exit");
			break;
		}
		case KeyInputEventTypeId: {
			char keyCode = *(char *)event->data;
			printf("\nNew Event >> Key `%c` (%i) was pressed", keyCode, keyCode);
			break;
		}
	}
}
