#include "GMTimer.h"


GMTimer::GMTimer(void)
{ //Initialize the variables
    mStartTicks = 0;
    mPausedTicks = 0;

    mPaused = false;
    mStarted = false;
}

void GMTimer::start()
{
    //Start the timer
    mStarted = true;

    //Unpause the timer
    mPaused = false;

    //Get the current clock time
    mStartTicks = SDL_GetTicks();
    mPausedTicks = 0;
}

void GMTimer::stop()
{
    //Stop the timer
    mStarted = false;

    //Unpause the timer
    mPaused = false;

    //Clear tick variables
    mStartTicks = 0;
    mPausedTicks = 0;
}

void GMTimer::pause()
{
    //If the timer is running and isn't already paused
    if( mStarted && !mPaused )
    {
        //Pause the timer
        mPaused = true;

        //Calculate the paused ticks
        mPausedTicks = SDL_GetTicks() - mStartTicks;
        mStartTicks = 0;
    }
}

Uint32 GMTimer::getTicks()
{
    //The actual timer time
    Uint32 time = 0;

    //If the timer is running
    if( mStarted )
    {
        //If the timer is paused
        if( mPaused )
        {
            //Return the number of ticks when the timer was paused
            time = mPausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            time = SDL_GetTicks() - mStartTicks;
        }
    }

    return time;
}

float GMTimer::getMilliseconds()
{
	int ticks = getTicks();
	float seconds = (float)ticks;
	return seconds;
}

float GMTimer::getSeconds()
{
	int ticks = getTicks();
	float seconds = (float)ticks / (float)1000;
	return seconds;
}

float GMTimer::getMinutes()
{
	int ticks = getTicks();
	float seconds = (float)ticks / (float)60000;
	return seconds;
}

int GMTimer::getWholeSeconds()
{
	return getTicks()/1000;
}

int GMTimer::getWholeMinutes()
{
	return getTicks()/60000;
}
bool GMTimer::isStarted()
{
    //Timer is running and paused or unpaused
    return mStarted;
}

bool GMTimer::isPaused()
{
    //Timer is running and paused
    return mPaused && mStarted;
}