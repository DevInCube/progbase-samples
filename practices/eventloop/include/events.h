/** @file
    @brief EventSystem Interface
*/

#pragma once

/**
	@typedef Event
*/
typedef struct Event Event;
/**
	@typedef EventHandler
	@brief a container for event handler information
*/
typedef struct EventHandler EventHandler;

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
	EventHandler * sender;  /**< pointer to an event handler that have raised this event */
	int type;  /**< an identifier of event type  */
	void * data;  /**< pointer to custom event data of type depending on event type */
	DestructorFunction destructor;  /**< a callback function pointer to call to free data */
};

Event * Event_new(EventHandler * sender, int type, void * data, DestructorFunction dest);
void Event_free(Event ** dataPtr);

/**
	@typedef EventHandlerFunction
	@brief a type for callback functions to call on event handlers on event occurance
	@param data - event handler data pointer
	@param event - newly raised event
*/
typedef void (*EventHandlerFunction)(EventHandler * data, Event * event);

/**
	@brief a structure that holds infomation about system event handlers
*/
struct EventHandler {
	void * data;  /**< a pointer to an event handler data */
	DestructorFunction destructor;  /**< a pointer to function that will be called to free data data*/
	EventHandlerFunction handler;  /**< a pointer to function that will call on data events handle */
};


/**
	@param data - an event handler data pointer
	@param destructor - a DestructorFunction function pointer to call on data data free
	@param eventHandler - an EventHandlerFunction callback to handle events for data event handler
*/
EventHandler * EventHandler_new(
	void * data, 
	DestructorFunction destructor, 
	EventHandlerFunction eventHandler);

/* public EventSystem API */

/**
	@brief initialize all EventSystem data
*/
void EventSystem_init(void);
/**
	@brief cleanup all EventSystem data
*/
void EventSystem_cleanup(void);
/**
	@brief start infinite event loop
*/
void EventSystem_loop(void);
/**
	@brief add new EventSystem event handler
*/
void EventSystem_addHandler(EventHandler * handler);
/**
	@brief remove new EventSystem event handler by it's data pointer'
*/
void EventSystem_removeHandler(EventHandler * handler);
/**
	@brief add new event to EventSystem to handle by event handlers
*/
void EventSystem_raiseEvent(Event * event);

/**
	@brief some base events type ids
*/
typedef enum { 
	StartEventTypeId = 1,  /**< the first event generated before event loop start */
	UpdateEventTypeId = 0,  /**< event is generated in every iteration of event loop */
	ExitEventTypeId = -1  /**< event to stop event loop */
} BaseEventTypes;