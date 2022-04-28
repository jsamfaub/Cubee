#pragma once
class LTimer
{
public:
	LTimer();

	Uint32 getTicks();
	void start();
	void stop();
	void pause();
	void resume();

	bool isStarted();
	bool isPaused();
private:
	bool started;
	bool paused;
	Uint32 startTicks;
	Uint32 pauseTicks;
};

