#pragma once

class Timer
{
public:
	Timer();
	~Timer();

	void Start(); //Triggers or resets the timer.

	double ReadMS(); // Read the miliseconds since “start” was called.

	double Read(); // Read the microseconds since “start” was called.

	double Stop(); // Stop the clock(+return current microseconds).
		// Any read from now on returns the same value until the clock is reset again.

	float FrameInfo();

	bool GetRegulateFramerate();
	void SetRegulateFramerate();
	bool GetDoubleFramerate();
	void SetDoubleFramerate();

private:
	unsigned start, startMS, previousFrameTime = 0;
	static unsigned frequency;
	int max30FPS = 30;
	double maxFT30 = 1000 / max30FPS;
	int max60FPS = 60;
	double maxFT60 = 1000 / max60FPS;
	bool regulateFramerate = false; 
	bool doubleFramerate = false;
};

