#include "Globals.h"
#include "ModuleTexture.h"
#include "DevIL/include/IL/il.h"
#include "DevIL/include/IL/ilu.h"
#include "SDL.h"
#include "GL/glew.h"
#include "MathGeoLib.h"

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

unsigned ModuleTexture::LoadTextureFromImage(const char* image, const char* fbx_name, unsigned program)
{
	unsigned imageID;
	//ilGenImages(1, &imageID);
	//ilBindImage(imageID);
	CONSOLELOG("Checking %s on the path described in the FBX.", image);
	bool loaded = ilLoadImage(image);
	if (!loaded) 
	{
		CONSOLELOG("%s not found, checking on the same folder you loaded the FBX.", image);
		
		// Catching same folder of fbx
		int finalFolder = strlen(fbx_name) - strlen(strrchr(fbx_name, '\\')) + 1;

		// Append folder path and image name
		std::string path;
		for (int i = 0; i < finalFolder; ++i)
		{
			path.push_back(fbx_name[i]);
		}
		for (int i = finalFolder; i - finalFolder < strlen(image); ++i)
		{
			path.push_back(image[i - finalFolder]);
		}
		const char* imagePath = path.c_str();

		bool loaded = ilLoadImage(imagePath);
		if (!loaded)
		{
			CONSOLELOG("%s not found, trying in 'Textures/' folder.", image);
			path.clear();

			// Append textures folder path and image name
			path.append("textures\\");
			path.append(image);
			const char* imagePath = path.c_str();

			bool loaded = ilLoadImage(imagePath);
			if (!loaded)
			{
				CONSOLELOG("%s not found, no texture will be used.", image);
			}
		}
	}

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

	ilDeleteImages(1, &imageID);

	return imageID;
}

unsigned ModuleTexture::LoadTextureFromImageDropped(const char* image, unsigned program)
{
	CONSOLELOG("Loading %s as a texture.", image);
	unsigned imageID;
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

	ilDeleteImages(1, &imageID);

	return imageID;
}
