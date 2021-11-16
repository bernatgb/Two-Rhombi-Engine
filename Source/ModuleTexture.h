#pragma once
#include "Module.h"
#include "Globals.h"

class ModuleTexture : public Module
{
public:
	ModuleTexture();
	~ModuleTexture();

	bool Init();
	update_status Update();
	bool CleanUp();

private:
	unsigned lennaTexture;
};
