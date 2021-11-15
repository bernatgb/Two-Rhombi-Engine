#include "Globals.h"
#include "Application.h"
#include "ModuleExercise.h"
#include "ModuleProgram.h"
#include "ModuleWindow.h"
#include "SDL.h"
#include "GL/glew.h"
#include "MathGeoLib.h"

ModuleExercise::ModuleExercise()
{
}

// Destructor
ModuleExercise::~ModuleExercise()
{
}

bool ModuleExercise::Init()
{
	// TRIANGLE
	// loads a triangle into a VBO with vertices: (-1, -1, 0) (1, -1, 0) (0, 1, 0)
	triangleVBO = CreateTriangleVBO();

	// creates a program with Hello World vertex and fragment shaders
	const char* vertexShaderLoaded = App->program->LoadShaderSource("..\\Source\\VertexShader.vert");
	const char* fragmentShaderLoaded = App->program->LoadShaderSource("..\\Source\\FragmentShader.frag");

	unsigned vertexShaderID = App->program->CompileShader(GL_VERTEX_SHADER, vertexShaderLoaded);
	
	unsigned fragmentShaderID = App->program->CompileShader(GL_FRAGMENT_SHADER, fragmentShaderLoaded);

	triangleProgram = App->program->CreateProgram(vertexShaderID, fragmentShaderID);

	// SQUARE
	squareVBO = CreateSquareVBO();
	
	// creates a program with Hello World vertex and fragment shaders
	//const char* vertexShaderLoaded = App->program->LoadShaderSource("..\\Source\\VertexShader.vert");
	//const char* fragmentShaderLoaded = App->program->LoadShaderSource("..\\Source\\FragmentShader.frag");
	
	//unsigned vertexShaderID = App->program->CompileShader(GL_VERTEX_SHADER, vertexShaderLoaded);
	//unsigned fragmentShaderID = App->program->CompileShader(GL_FRAGMENT_SHADER, fragmentShaderLoaded);

	squareProgram = App->program->CreateProgram(vertexShaderID, fragmentShaderID);
	
	return true;
}

update_status ModuleExercise::Update()
{
	// renders VBO triangle using Hello World program
	RenderTriangleVBO(triangleVBO, triangleProgram);

	// reders VBO square using Hello World program
	//RenderSquareVBO(squareVBO, squareProgram);

	return UPDATE_CONTINUE;
}

bool ModuleExercise::CleanUp()
{
	glDeleteBuffers(1, &triangleVBO);

	glDeleteBuffers(1, &squareVBO);

	return true;
}

unsigned ModuleExercise::CreateTriangleVBO()
{
	float vtx_data[] = { -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f };

	unsigned vbo;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // set vbo active
	glBufferData(GL_ARRAY_BUFFER, sizeof(vtx_data), vtx_data, GL_STATIC_DRAW);

	return vbo;
}

unsigned ModuleExercise::CreateSquareVBO()
{
	float vtx_data[] = { -0.5f, -0.5f, 0.0f, 
						  0.5f, -0.5f, 0.0f,
						 -0.5f,  0.5f, 0.0f,
						  0.5f,  0.5f, 0.0f, };

	unsigned vbo;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // set vbo active
	glBufferData(GL_ARRAY_BUFFER, sizeof(vtx_data), vtx_data, GL_STATIC_DRAW);

	return vbo;
}

void ModuleExercise::RenderTriangleVBO(unsigned vbo, unsigned program)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);

	// size = 3 float per vertex
	// stride = 0 is equivalent to stride = sizeof(float)*3
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glUseProgram(program);

	float4x4 model, view, projection;
	// TODO: retrieve model view and projection
	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE, &model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_TRUE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "proj"), 1, GL_TRUE, &projection[0][0]);
	// TODO: bind buffer and vertex attributes

	// 1 triangle to draw = 3 vertices
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void ModuleExercise::RenderSquareVBO(unsigned vbo, unsigned program)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);

	// size = 3 float per vertex
	// stride = 0 is equivalent to stride = sizeof(float)*3
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glUseProgram(program);

	// 2 triangle to draw = 4 vertices
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
