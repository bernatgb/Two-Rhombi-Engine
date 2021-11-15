#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleExercise;
class ModuleProgram;
class ModuleGUI;

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

private:

	std::list<Module*> modules;

};

extern Application* App;
