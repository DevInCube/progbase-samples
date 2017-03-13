#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <thread>
#include <events.h>

using namespace std;

vector<EventHandler *> EventSystem::handlers;
queue<Event *> EventSystem::events;

void EventSystem::init() {
	cout << "init()" << endl;
}

void EventSystem::cleanup() {
	cout << "cleanup()" << endl;
}

void EventSystem::loop() {
	cout << "loop()" << endl;
	EventSystem::raiseEvent(new StartEvent());
	while (true) {
		EventSystem::raiseEvent(new UpdateEvent());
		while (EventSystem::events.size() > 0) {
			Event * event = EventSystem::events.front();
			EventSystem::events.pop();
			for (EventHandler * handler : EventSystem::handlers) {
				handler->handleEvent(event);
			} 
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(33));
	}
}

Event::~Event() { }
EventHandler::~EventHandler() { }

void EventSystem::exit() {
	cout << "exit()" << endl;
}

void EventSystem::addHandler(EventHandler * eventHandler) {
	EventSystem::handlers.push_back(eventHandler);
}

void EventSystem::removeHandler(EventHandler * eventHandler) {
	// @todo
}

void EventSystem::raiseEvent(Event * event) {
	EventSystem::events.push(event);
}
