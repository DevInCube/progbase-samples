#pragma once

#include <vector>
#include <queue>

using namespace std;

class Event {
public:
	virtual ~Event(void);
	virtual int getType(void) = 0;
};

class EventHandler {
public:
	virtual ~EventHandler(void) ;
	virtual void handleEvent(Event * event) = 0;
};

class EventSystem {
private:
	static vector<EventHandler *> handlers;
	static queue<Event *> events;

public:
	static void init(void);
	static void cleanup(void);
	static void loop(void);
	static void exit(void);
	static void raiseEvent(Event * event);
	static void addHandler(EventHandler * eventHandler);
	static void removeHandler(EventHandler * eventHandler);
};

class StartEvent : public Event {
public:
	static const int type = -234234;
	int getType(void) { return StartEvent::type; }
};

class UpdateEvent : public Event {
public:
	static const int type = -12323;
	int getType(void) { return UpdateEvent::type; }
};
