#pragma once

class Timer
{
public:
	Timer();
	~Timer();

	void Start(); //Triggers or resets the timer.

	double Read(); // Read the microseconds since “start” was called.

	double Stop(); // Stop the clock(+return current microseconds).
		// Any read from now on returns the same value until the clock is reset again.

private:
	unsigned start = 0;
	static unsigned frequency;
};

