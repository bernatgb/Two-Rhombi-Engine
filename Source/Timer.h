#pragma once

class Timer
{
public:
	Timer();
	~Timer();

	void Start(); //Triggers or resets the timer.

	double ReadMS(); // Read the miliseconds since “start” was called.

	double Read4FrameInfo(); // Read the miliseconds since last time this function was called.

	double Read(); // Read the microseconds since “start” was called.

	double Stop(); // Stop the clock(+return current microseconds).
		// Any read from now on returns the same value until the clock is reset again.

	float FrameInfo();

private:
	unsigned start, startMS, previousFrameTime = 0;
	static unsigned frequency;
	int maxFPS = 30;
};

