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
	unsigned LoadTextureFromMaterial(unsigned image, unsigned program);
	unsigned LoadTextureFromImage(const char* image, const char* fbx_name, unsigned program);
	unsigned LoadTextureFromImageDropped(const char* image, unsigned program);

private:
	//unsigned imageID;
};
