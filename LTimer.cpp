#include <SDL2/SDL.h>
#include "LTimer.h"

LTimer::LTimer()
{
	started = 0;
	paused = 0;
	startTicks = 0;
	pauseTicks = 0;
}

Uint32 LTimer::getTicks()
{
	Uint32 time = 0;

	if (started)
	{
		if (paused)
		{
			time = pauseTicks;
		}
		else
		{
			time = SDL_GetTicks() - startTicks;
		}
	}

	return time;
}

void LTimer::start()
{
	started = 1;
	paused = 0;

	startTicks = SDL_GetTicks();
	pauseTicks = 0;
}

void LTimer::stop()
{
	started = 0;
	paused = 0;

	startTicks = 0;
	pauseTicks = 0;
}

void LTimer::pause()
{
	if (started && !paused)
	{
		paused = 1;
		pauseTicks = SDL_GetTicks() - startTicks;
		startTicks = 0;
	}
}

void LTimer::resume()
{
	if (started && paused)
	{
		paused = 0;

		startTicks = SDL_GetTicks() - startTicks;

		pauseTicks = 0;
	}
}

bool LTimer::isStarted()
{
	return started;
}

bool LTimer::isPaused()
{
	return paused;
}
