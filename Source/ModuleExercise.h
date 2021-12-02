#pragma once
#include "Module.h"
#include "Globals.h"
#include "Model.h"
#include "MathGeoLib.h"

class ModuleExercise : public Module
{
public:
	ModuleExercise();
	~ModuleExercise();

	bool Init();
	update_status Update();
	bool CleanUp();

	unsigned CreateTriangleVBO();
	unsigned CreateSquareVBO();
	void RenderTriangleVBO(unsigned vbo, unsigned program);
	void RenderSquareVBO(unsigned vbo, unsigned program);
	void RenderBakerhouse(unsigned program);
	void RenderModel();
	void ModelDropped(const char* file);

	Model model;

private:
	unsigned triangleVBO;
	unsigned triangleProgram;
	unsigned squareVBO;
	unsigned squareProgram;
	unsigned bakerhouseProgram;
	unsigned modelProgram;
	const char* fbxFile;
	const char* imageFile;
};
