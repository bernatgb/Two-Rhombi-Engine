#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"
#include "SDL/include/SDL.h"

class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow();

	// Destructor
	virtual ~ModuleWindow();

	// Called before render is available
	bool Init();

	// Called before updating
	update_status PreUpdate();

	// Called before quitting
	bool CleanUp();

public:
	//The window we'll be rendering to
	SDL_Window* window = NULL;

	//The surface contained by the window
	SDL_Surface* screen_surface = NULL;

	double aspectRatio = 0;
	int previousWidth = SCREEN_WIDTH;
	int previousHeight = SCREEN_HEIGHT;
};

#endif // __ModuleWindow_H__