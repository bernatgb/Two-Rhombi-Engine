#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleCamera.h"

ModuleWindow::ModuleWindow()
{
}

// Destructor
ModuleWindow::~ModuleWindow()
{
}

// Called before render is available
bool ModuleWindow::Init()
{
	LOG("Init SDL window & surface");
	bool ret = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		//Create window
		int width = SCREEN_WIDTH;
		int height = SCREEN_HEIGHT;
		aspectRatio = (double)width / (double)height;
		flags = SDL_WINDOW_SHOWN |  SDL_WINDOW_OPENGL;

		if(FULLSCREEN == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		if (RESIZABLE == true)
		{
			flags |= SDL_WINDOW_RESIZABLE;
		}

		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

		if(window == NULL)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			//Get window surface
			
			screen_surface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}

update_status ModuleWindow::PreUpdate()
{
	screen_surface = SDL_GetWindowSurface(window);
	double newAspectRatio = (double)screen_surface->w / (double)screen_surface->h;
	if (newAspectRatio != aspectRatio)
	{
		App->renderer->WindowResized(screen_surface->w, screen_surface->h);
		
		if (screen_surface->w != previousWidth)
		{
			App->camera->WindowResized(newAspectRatio, true);
			previousWidth = screen_surface->w;
		}
		if (screen_surface->h != previousHeight)
		{
			App->camera->WindowResized(newAspectRatio, false);
			previousHeight = screen_surface->h;
		}

		aspectRatio = newAspectRatio;
	}
		

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleWindow::CleanUp()
{
	LOG("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if(window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}

void ModuleWindow::SetFullscreen(bool fullscreen)
{
	if (fullscreen)
	{
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		SDL_SetWindowFullscreen(window, flags);
	}
	else
	{
		flags -= SDL_WINDOW_FULLSCREEN_DESKTOP;
		SDL_SetWindowFullscreen(window, flags);
	}
}

void ModuleWindow::SetResizable(bool resizable)
{
	SDL_SetWindowResizable(window, (SDL_bool)resizable);
}
