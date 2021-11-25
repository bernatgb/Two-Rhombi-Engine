#pragma once
#include "Module.h"
#include "Globals.h"
#include "SDL.h"
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
	HardwareInfo hardware;
	std::vector<float> fps_log;
	std::vector<float> ms_log;
};
