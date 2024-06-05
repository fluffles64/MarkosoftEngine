#pragma once
#include "Singleton.h"
#include "SDL.h"

class TimeManager : public Singleton<TimeManager>
{
	friend class Singleton<TimeManager>;
private:
	//The clock time when the timer started
	Uint32 mStartTicks;

	//The ticks stored when the timer was paused
	Uint32 mPausedTicks;

	//The timer status
	bool mPaused;
	bool mStarted;

public:
	//Initializes variables
	TimeManager();

	//The various clock actions
	void start();
	void stop();
	void pause();
	void unpause();

	//Gets the timer's time
	Uint32 getTicks();

	//Checks the status of the timer
	bool isStarted();
	bool isPaused();
};