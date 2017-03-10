#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <list.h>
#include <events.h>
#include <progbase.h>
#include <pbconsole.h>

/* custom constant event type ids*/
enum {
	CustomEventTypeId = 47578
};

/* event handler functions prototypes */
void CustomHandler_update(EventHandler * self, Event * event);

int main(void) {
	// startup event system
	EventSystem_init();

	// add event handlers
	EventSystem_addHandler(EventHandler_new(NULL, NULL, CustomHandler_update));

	// start infinite event loop
	EventSystem_loop();
	// cleanup event system
	EventSystem_cleanup();
	return 0;
}

/* event handlers functions implementations */

void CustomHandler_update(EventHandler * self, Event * event) {
	switch (event->type) {
		case StartEventTypeId : {
			printf("START!\n");
			break;
		}
		case UpdateEventTypeId : {
			void * data = event->data;
			double updateMillis = *(double *)data;
			printf("Update event with data: %.1lf millis\n", updateMillis);
			fflush(stdout);
			sleepMillis(1000);
			break;
		}
	}
}