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

	unsigned LoadImage(const char* image);
	void LoadTexture(unsigned program);

private:
	unsigned imageID;
};
