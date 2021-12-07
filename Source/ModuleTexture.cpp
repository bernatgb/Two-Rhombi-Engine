#include "Globals.h"
#include "ModuleTexture.h"
#include "DevIL/include/IL/il.h"
#include "DevIL/include/IL/ilu.h"
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
	ilInit();

	return true;
}

update_status ModuleTexture::Update()
{
	return UPDATE_CONTINUE;
}

bool ModuleTexture::CleanUp()
{
	//glDeleteTextures(1, &imageID);

	return true;
}

unsigned ModuleTexture::LoadImage(const char* image)
{
	// Load image data with DevIL into CPU
	unsigned imageID;
	ilGenImages(1, &imageID);
	ilBindImage(imageID);
	ilLoadImage(image);
	iluFlipImage();
	return imageID;
}

void ModuleTexture::LoadTexture(unsigned program)
{
	// Create and load OpenGL texture into GPU
	unsigned imageID;
	glGenTextures(1, &imageID);
	glBindTexture(GL_TEXTURE_2D, imageID);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); /* We will use linear
	 interpolation for magnification filter */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); /* We will use linear
	  interpolation for minifying filter */

	glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH),
		ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE,
		ilGetData());

	glGenerateMipmap(GL_TEXTURE_2D);
	//glGenerateTextureMipmap(imageID);

	// Add texture coordinates (UVs) into VBO
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, imageID);
	glUniform1i(glGetUniformLocation(program, "imageID"), 0);

	ilDeleteImages(1, &imageID);
}

unsigned ModuleTexture::LoadTextureFromMaterial(unsigned image, unsigned program)
{
	glGenTextures(1, &image);
	glBindTexture(GL_TEXTURE_2D, image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); /* We will use linear
	 interpolation for magnification filter */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); /* We will use linear
	  interpolation for minifying filter */

	glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH),
		ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE,
		ilGetData());

	return image;
}

unsigned ModuleTexture::LoadTextureFromImage(const char* image, unsigned program)
{
	unsigned imageID;
	//ilGenImages(1, &imageID);
	//ilBindImage(imageID);
	ilLoadImage(image);
	iluFlipImage();

	glGenTextures(1, &imageID);
	glBindTexture(GL_TEXTURE_2D, imageID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); /* We will use linear
	 interpolation for magnification filter */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); /* We will use linear
	  interpolation for minifying filter */

	glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH),
		ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE,
		ilGetData());

	return imageID;
}
