#include "Globals.h"
#include "Application.h"
#include "ModuleExercise.h"
#include "ModuleProgram.h"
#include "ModuleWindow.h"
#include "SDL.h"
#include "GL/glew.h"
#include "il.h"
#include "ilu.h"

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
	const char* fragmentShaderLoaded = App->program->LoadShaderSource("..\\Soure\\FragmentShader.frag");

	unsigned vertexShaderID = App->program->CompileShader(GL_VERTEX_SHADER, vertexShaderLoaded);
	unsigned fragmentShaderID = App->program->CompileShader(GL_FRAGMENT_SHADER, fragmentShaderLoaded);

	triangleProgram = App->program->CreateProgram(vertexShaderID, fragmentShaderID);

	// SQUARE
	squareVBO = CreateSquareVBO();

	// creates a program with Hello World vertex and fragment shaders
	vertexShaderLoaded = App->program->LoadShaderSource("..\\Source\\VertexShader.vert");
	fragmentShaderLoaded = App->program->LoadShaderSource("..\\Soure\\FragmentShader.frag");

	vertexShaderID = App->program->CompileShader(GL_VERTEX_SHADER, vertexShaderLoaded);
	fragmentShaderID = App->program->CompileShader(GL_FRAGMENT_SHADER, fragmentShaderLoaded);

	squareProgram = App->program->CreateProgram(vertexShaderID, fragmentShaderID);

	return true;
}

update_status ModuleExercise::Update()
{
	// renders VBO triangle using Hello World program
	//App->program->RenderTriangleVBO(triangleVBO, triangleProgram);

	// reders VBO square using Hello World program
	App->program->RenderSquareVBO(triangleVBO, triangleProgram);

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
