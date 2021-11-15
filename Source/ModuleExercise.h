#pragma once
#include "Module.h"
#include "Globals.h"

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

private:
	unsigned triangleVBO;
	unsigned triangleProgram;
	unsigned squareVBO;
	unsigned squareProgram;
};
