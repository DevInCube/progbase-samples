/** @file
    @brief EventSystem Interface
*/

#ifndef MODULE_H
#define MODULE_H

typedef struct Event Event;

/**
	@typedef DestructorFunction
	@brief a pointer type for functions that can free generic pointed data
*/
typedef void (*DestructorFunction)(void * data);

/**
	@struct Event
	@brief a structure that holds information about an event occured
*/
struct Event {
	void * sender;  /**< pointer to an actor that have raised this event */
	int type;  /**< an identifier of event type  */
	void * data;  /**< pointer to custom event data of type depending on event type */
	DestructorFunction destructor;  /**< a callback function pointer to call to free data */
};

Event * Event_new(void * sender, int type, void * data, DestructorFunction dest);
void Event_free(Event ** dataPtr);

/**
	@typedef EventHandler
	@brief a container for actor information
*/
typedef struct EventHandler EventHandler;

/**
	@typedef EventHandlerFunction
	@brief a type for callback functions to call on actors on event occurance
	@param data - actor data pointer
	@param event - newly raised event
*/
typedef void (*EventHandlerFunction)(EventHandler * data, Event * event);

/**
	@brief a structure that holds infomation about system actors
*/
struct EventHandler {
	void * data;  /**< a pointer to an actor data */
	DestructorFunction destructor;  /**< a pointer to function that will be called to free data data*/
	EventHandlerFunction handler;  /**< a pointer to function that will call on data events handle */
};


/**
	@param data - an actor data pointer
	@param destructor - a DestructorFunction function pointer to call on data data free
	@param eventHandler - an EventHandlerFunction callback to handle events for data actor
*/
EventHandler * EventHandler_new(
	void * data, 
	DestructorFunction destructor, 
	EventHandlerFunction eventHandler);

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
void EventSystem_addHandler(EventHandler * handler);
/**
	@brief remove new EventSystem actor by it's data pointer'
*/
void EventSystem_removeHandler(EventHandler * handler);
/**
	@brief add new event to EventSystem to handle by actors
*/
void EventSystem_raiseEvent(Event * event);

/**
	@brief some base events type ids
*/
typedef enum { 
	ExitEventTypeId = -1,
	UpdateEventTypeId = 0,
	StartEventTypeId = 1,
	RemoveHandlerEventTypeId = 767456
} BaseEventTypes;

#endif
