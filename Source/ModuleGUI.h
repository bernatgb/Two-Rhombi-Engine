#pragma once
#include "Module.h"
#include "Globals.h"
#include "Timer.h"
#include "Console.h"
#include "SDL.h"
#include "imgui.h"
#include <vector>

struct HardwareInfo
{
	SDL_version sdl_version;
	int n_cpu;
	float ram_gb;
	unsigned char* gpu;
	unsigned char* gpu_brand;
	int vram_budget;
	int vram_free;
};

struct SoftwareInfo
{
	SDL_version sdl_version;
	char* gl_version;
};

class ModuleGUI : public Module
{
public:
	ModuleGUI();
	~ModuleGUI();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	update_status Draw();

private:
	bool demo = false;
	bool show_app_log = false;
	HardwareInfo hardware;
	SoftwareInfo software;
	std::vector<float> fps_log;
	std::vector<float> ms_log;
	bool fullscreen = false;
	bool resizable = true;
	int index = 0;
	bool complete = false;
	Timer timer;
	bool regulateFramerate;
	bool doubleFramerate;
	bool notDoubleFramerate;
};
