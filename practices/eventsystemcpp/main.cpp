#include <iostream>
#include <events.h>
#include <pbconsole.h>

using namespace std;

class CustomHandler: public EventHandler {
public:
	void handleEvent(Event * event) {
		switch (event->getType()) {
			case StartEvent::type: {
				cout << "<<STARTED>>" << endl;
				break;
			}
			case UpdateEvent::type: {
				cout << '.' << flush;
				break;
			}
		}
	}
};

int main(void) {
	// startup event system
	EventSystem::init();

	// add event handlers
	EventSystem::addHandler(new CustomHandler());

	// start infinite event loop
	EventSystem::loop();
	// cleanup event system
	EventSystem::cleanup();
	return 0;
}

/* event handlers functions implementations */

// void KeyInputHandler_update(EventHandler * self, Event * event) {
// 	if (conIsKeyDown()) {  // non-blocking key input check
// 		char * keyCode = malloc(sizeof(char));
// 		*keyCode = getchar();
// 		EventSystem_raiseEvent(Event_new(self, KeyInputEventTypeId, keyCode, free));
// 	}
// }

// void Listener_update(EventHandler * self, Event * event) {
// 	switch(event->type) {
// 		case StartEventTypeId: {
// 			puts("Program Started! Press [Esc] to exit");
// 			break;
// 		}
// 		case UpdateEventTypeId: {
// 			putchar('.');
// 			break;
// 		}
// 		case ExitEventTypeId: {
// 			puts("Program Stopped! Bye!");
// 			puts("");
// 			break;
// 		}
// 		case KeyInputEventTypeId: {
// 			char keyCode = *(char *)event->data;
// 			printf("\nNew Event >> Key `%c` (%i) was pressed\n", keyCode, keyCode);
// 			if (keyCode == 27) {  // Escape key code
// 				puts("Exit program call");
// 				EventSystem_exit();	
// 			}
// 			break;
// 		}
// 	}
// }
