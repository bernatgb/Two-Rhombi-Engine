#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTexture;
class ModuleInput;
class ModuleExercise;
class ModuleProgram;
class ModuleGUI;
class ModuleDebugDraw;
class ModuleCamera;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	ModuleRender* renderer = nullptr;
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleExercise* exercise = nullptr;
	ModuleProgram* program = nullptr;
	ModuleGUI* gui = nullptr;
	ModuleDebugDraw* debugDraw = nullptr;
	ModuleTexture* texture = nullptr;
	ModuleCamera* camera = nullptr;

private:

	std::list<Module*> modules;

};

extern Application* App;
