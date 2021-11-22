#include "Timer.h"
#include "SDL/include/SDL.h"

unsigned Timer::frequency = SDL_GetPerformanceFrequency();

Timer::Timer()
{}

Timer::~Timer()
{}

void Timer::Start()
{
	//start = SDL_GetTicks();
	start = SDL_GetPerformanceCounter();
}

double Timer::Read()
{
	//return SDL_GetTicks() - start;
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
