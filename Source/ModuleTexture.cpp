#include "Globals.h"
#include "ModuleTexture.h"
#include "DevIL/include/IL/il.h"
#include "SDL.h"
#include "GL/glew.h"

ModuleTexture::ModuleTexture()
{
}

// Destructor
ModuleTexture::~ModuleTexture()
{
}

bool ModuleTexture::Init()
{
	// Load image data with DevIL into CPU
	//ilLoadImage("..\\Source\\Lenna");

	// Create and load OpenGL texture into GPU
	//glGenTextures(1, &lennaTexture);
	
	// Add texture coordinates (UVs) into VBO
	//glActiveTexture(lennaTexture);

	return true;
}

update_status ModuleTexture::Update()
{
	return UPDATE_CONTINUE;
}

bool ModuleTexture::CleanUp()
{
	//glDeleteTextures(1, &lennaTexture);

	return true;
}