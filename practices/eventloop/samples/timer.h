#pragma once

/* timer states */
typedef enum {
	T_STOPPED,
	T_STARTED,
	T_PAUSED,
	T_ELAPSED
} TimerState;
/* timer type */
typedef struct Timer Timer;
Timer * Timer_new(double maxTime);
void Timer_free(Timer * self);
/* input events */
void Timer_start(Timer * self);
void Timer_pause(Timer * self);
void Timer_reset(Timer * self);  // same as stop
void Timer_update(Timer * self, double elapsed);
/* getters */
TimerState Timer_getState(Timer * self);
double Timer_getMaxTime(Timer * self);
double Timer_getElasedTime(Timer * self);

/* @todo move to implementation */
struct Timer {
	TimerState state;
	double maxTime;
	double elapsedTime;
};
