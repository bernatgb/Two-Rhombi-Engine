#pragma once
#include "Module.h"
#include "Globals.h"
#include "SDL/include/SDL.h"

typedef unsigned __int8 Uint8;

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status Update();
	bool CleanUp();

private:
	const Uint8 *keyboard = NULL;
	bool rshiftWasPressed = false;
	bool lshiftWasPressed = false;
	bool mouseLButtonDown = false;
	Sint32 x = 0;
	bool xUpdated = false;
};