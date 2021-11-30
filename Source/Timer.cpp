#include "Timer.h"
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

double Timer::Read4FrameInfo()
{
	double now = SDL_GetTicks();
	double actualFrameTime = now - previousFrameTime;
	previousFrameTime = now;
	return actualFrameTime;
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
	float frame_time = Read4FrameInfo();
	float fps = (frame_time > 0) ? 1000.0f / frame_time : 0.0f;
	// Regulate Framerate 
	/*
	if (fps > maxFPS)
	{
		SDL_Delay(fps - maxFPS);
	}
	*/
	return fps;
}
