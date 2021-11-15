#pragma once
#include "Module.h"
#include "Globals.h"

class ModuleProgram : public Module
{
public:
	ModuleProgram();
	~ModuleProgram();

	bool Init();
	bool CleanUp();

	char* LoadShaderSource(const char* shader_file_name);
	unsigned CompileShader(unsigned type, const char* source);
	unsigned CreateProgram(unsigned vertex_s, unsigned fragment_s);
	void RenderTriangleVBO(unsigned vbo, unsigned program);
	void RenderSquareVBO(unsigned vbo, unsigned program);

private:

	const char* vertexshader;
	const char* fragmentshader;
};