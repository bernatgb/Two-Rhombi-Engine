#include "Timer.h"
#include "Globals.h"
#include "SDL/include/SDL.h"

unsigned Timer::frequency = SDL_GetPerformanceFrequency();

Timer::Timer()
{}

Timer::~Timer()
{}

void Timer::Start()
{
	startMS = previousFrameTime = SDL_GetTicks();
	start = SDL_GetPerformanceCounter();
}

double Timer::ReadMS()
{
	return SDL_GetTicks() - startMS;
}

double Timer::Read()
{
	return SDL_GetPerformanceCounter() - start;
}

double Timer::Stop()
{
	double finish = Read();
	finish /= SDL_GetPerformanceFrequency();
	start = 0;
	SDL_Log("1 million iterations of ticktock took %f ms", finish * 1000);
	return finish;
}

float Timer::FrameInfo()
{
	double now = SDL_GetTicks();
	double actualFrameTime = now - previousFrameTime;

	// Regulate Framerate 
	if (regulateFramerate)
	{
		if (!doubleFramerate)
		{	
			if (maxFT30 > actualFrameTime)
			{
				SDL_Delay(maxFT30 - actualFrameTime);
				actualFrameTime = SDL_GetTicks() - previousFrameTime;
			}
		}
		else
		{
			if (maxFT60 > actualFrameTime)
			{
				SDL_Delay(maxFT60 - actualFrameTime);
				actualFrameTime = SDL_GetTicks() - previousFrameTime;
			}
		}
	}
	previousFrameTime = now;

	float fps = (actualFrameTime > 0) ? 1000.0f / actualFrameTime : 0.0f;

	return fps;
}

bool Timer::GetRegulateFramerate() 
{
	return regulateFramerate;
}

void Timer::SetRegulateFramerate()
{
	regulateFramerate = !regulateFramerate;
}

bool Timer::GetDoubleFramerate()
{
	return doubleFramerate;
}

void Timer::SetDoubleFramerate()
{
	doubleFramerate = !doubleFramerate;
}
