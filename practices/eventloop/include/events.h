/** @file
    @brief EventSystem Interface
*/

#ifndef MODULE_H
#define MODULE_H

typedef struct Event Event;

/**
	@typedef Destructor
	@brief a pointer type for functions that can free generic pointed data
*/
typedef void (*Destructor)(void * dataPtr);

/**
	@struct Event
	@brief a structure that holds information about an event occured
*/
struct Event {
	void * sender;  /**< pointer to an actor that have raised this event */
	int type;  /**< an identifier of event type  */
	void * data;  /**< pointer to custom event data of type depending on event type */
	Destructor destructor;  /**< a callback function pointer to call to free data */
};

Event * Event_new(void * sender, int type, void * data, Destructor dest);
void Event_free(Event ** selfPtr);

/**
	@typedef EventHandler
	@brief a type for callback functions to call on actors on event occurance
	@param self - actor data pointer
	@param event - newly raised event
*/
typedef void (*EventHandler)(void * self, Event * event);

/**
	@typedef HandlerObject
	@brief a container for actor information
*/
typedef struct HandlerObject HandlerObject;

/**
	@param data - an actor data pointer
	@param dest - a destructor function pointer to call on self data free
	@param handler - an EventHandler callback to handle events for data actor
*/
HandlerObject * HandlerObject_new(void * data, Destructor dest, EventHandler handler);

/**
	@brief initialize all EventSystem data
*/
void EventSystem_init(void);
/**
	@brief cleanup all EventSystem data
*/
void EventSystem_deinit(void);
/**
	@brief start infinite event loop
*/
void EventSystem_loop(void);
/**
	@brief add new EventSystem actor
*/
void EventSystem_addHandler(HandlerObject * handler);
/**
	@brief remove new EventSystem actor by it's data pointer'
*/
void EventSystem_removeHandler(void * handler);
/**
	@brief add new event to EventSystem to handle by actors
*/
void EventSystem_raiseEvent(Event * event);

enum { 
	ExitEventTypeId = -1,
	UpdateEventTypeId = 0,
	StartEventTypeId = 1,
	RemoveHandlerEventTypeId = 767456
};

#endif
