#include "Globals.h"
#include "Application.h"
#include "ModuleExercise.h"
#include "ModuleCamera.h"
#include "ModuleTexture.h"
#include "ModuleProgram.h"
#include "ModuleWindow.h"
#include "Model.h"
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
	/*
	// TRIANGLE
	// loads a triangle into a VBO with vertices: (-1, -1, 0) (1, -1, 0) (0, 1, 0)
	triangleVBO = CreateTriangleVBO();

	// creates a program with Hello World vertex and fragment shaders
	const char* vertexShaderLoadedT = App->program->LoadShaderSource("..\\Source\\VertexShader.vert");
	const char* fragmentShaderLoadedT = App->program->LoadShaderSource("..\\Source\\FragmentShader.frag");

	unsigned vertexShaderIDt = App->program->CompileShader(GL_VERTEX_SHADER, vertexShaderLoadedT);
	
	unsigned fragmentShaderIDt = App->program->CompileShader(GL_FRAGMENT_SHADER, fragmentShaderLoadedT);

	triangleProgram = App->program->CreateProgram(vertexShaderIDt, fragmentShaderIDt);

	// SQUARE
	squareVBO = CreateSquareVBO();
	
	// creates a program with Hello World vertex and fragment shaders
	const char* vertexShaderLoadedS = App->program->LoadShaderSource("..\\Source\\VertexShader.vert");
	const char* fragmentShaderLoadedS = App->program->LoadShaderSource("..\\Source\\FragmentShader.frag");
	
	unsigned vertexShaderIDs = App->program->CompileShader(GL_VERTEX_SHADER, vertexShaderLoadedS);
	unsigned fragmentShaderIDs = App->program->CompileShader(GL_FRAGMENT_SHADER, fragmentShaderLoadedS);

	squareProgram = App->program->CreateProgram(vertexShaderIDs, fragmentShaderIDs);
	
	// BAKERHOUSE
	const char* vertexShaderLoadedB = App->program->LoadShaderSource("..\\Source\\VertexShader.vert");
	const char* fragmentShaderLoadedB = App->program->LoadShaderSource("..\\Source\\FragmentShader.frag");

	unsigned vertexShaderIDb = App->program->CompileShader(GL_VERTEX_SHADER, vertexShaderLoadedB);
	unsigned fragmentShaderIDb = App->program->CompileShader(GL_FRAGMENT_SHADER, fragmentShaderLoadedB);

	bakerhouseProgram = App->program->CreateProgram(vertexShaderIDb, fragmentShaderIDb);
	*/

	const char* vertexShaderLoaded = App->program->LoadShaderSource("..\\Source\\VertexShader.vert");
	const char* fragmentShaderLoaded = App->program->LoadShaderSource("..\\Source\\FragmentShader.frag");

	unsigned vertexShaderID = App->program->CompileShader(GL_VERTEX_SHADER, vertexShaderLoaded);
	unsigned fragmentShaderID = App->program->CompileShader(GL_FRAGMENT_SHADER, fragmentShaderLoaded);

	modelProgram = App->program->CreateProgram(vertexShaderID, fragmentShaderID);

	//imageFile = "..\\Source\\baker_house_model\\Baker_house.png";
	//fbxFile = "BakerHouse.fbx";
	fbxFile = "Dragon 2.5_fbx.fbx"; 
	//fbxFile = "DoubleDeckerBus.fbx";

	model.Load(imageFile, fbxFile, modelProgram);

	return true;
}

update_status ModuleExercise::Update()
{
	// renders VBO triangle using Hello World program
	//RenderTriangleVBO(triangleVBO, triangleProgram);

	// renders VBO square using Hello World program
	//RenderSquareVBO(squareVBO, squareProgram);

	// renders a bakerhouse
	//RenderBakerhouse(bakerhouseProgram);

	// renders the model
	RenderModel(modelProgram);

	return UPDATE_CONTINUE;
}

bool ModuleExercise::CleanUp()
{
	glDeleteBuffers(1, &triangleVBO);
	glDeleteBuffers(1, &squareVBO);

	glDeleteProgram(triangleProgram);
	glDeleteProgram(squareProgram);
	glDeleteProgram(bakerhouseProgram);
	glDeleteProgram(modelProgram);

	model.Clear();

	return true;
}

unsigned ModuleExercise::CreateTriangleVBO()
{
	float vtx_data[] = { -1.0f, -1.0f, 0.0f, // v0 pos
						  1.0f, -1.0f, 0.0f, // v1 pos
						  0.0f,  1.0f, 0.0f, // v2 pos

							0.0f, 0.0f,	// v0 texcoord
							1.0f, 0.0f, // v1 texcoord
							0.5f, 1.0f  // v2 texcoord
						};

	unsigned vbo;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // set vbo active
	glBufferData(GL_ARRAY_BUFFER, sizeof(vtx_data), vtx_data, GL_STATIC_DRAW);

	return vbo;
}

unsigned ModuleExercise::CreateSquareVBO()
{
	float vtx_data[] = { -0.5f, -0.5f, 0.0f, // v0 pos
						  0.5f, -0.5f, 0.0f, // v1 pos
						 -0.5f,  0.5f, 0.0f, // v2 pos
						  0.5f,  0.5f, 0.0f, // v3 pos

							1.0f, 0.0f,		 // v0 texcoord
							0.0f, 0.0f,		 // v1 texcoord
							1.0f, 1.0f,		 // v2 texcoord
							0.0f, 1.0f		 // v3 texcoord
	};
	/*
	float vtx_data[] = { -0.5f, -0.5f, 0.0f, // v0 pos
						  0.0f, 0.0f,		 // v0 texcoord

						  0.5f, -0.5f, 0.0f, // v1 pos
						  1.0f, 0.0f,		 // v1 texcoord

						 -0.5f,  0.5f, 0.0f, // v2 pos
						  0.0f, 1.0f,		 // v2 texcoord

						  0.5f,  0.5f, 0.0f, // v3 pos
						  1.0f, 1.0f		 // v3 texcoord
	};
	*/

	unsigned vbo;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // set vbo active
	glBufferData(GL_ARRAY_BUFFER, sizeof(vtx_data), vtx_data, GL_STATIC_DRAW);

	return vbo;
}

void ModuleExercise::RenderTriangleVBO(unsigned vbo, unsigned program)
{
	glUseProgram(program);

	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE, &App->camera->GetModelMatrix()[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_TRUE, &App->camera->GetViewMatrix()[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "proj"), 1, GL_TRUE, &App->camera->GetProjectionMatrix()[0][0]);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);

	// size = 3 float per vertex
	// stride = 0 is equivalent to stride = sizeof(float)*3
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Texture
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * 3 * 3));

	App->texture->LoadImage("..\\Source\\Lenna.png");
	App->texture->LoadTexture(program);
		
	// 1 triangle to draw = 3 vertices
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void ModuleExercise::RenderSquareVBO(unsigned vbo, unsigned program)
{
	glUseProgram(program);

	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE, &App->camera->GetModelMatrix()[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_TRUE, &App->camera->GetViewMatrix()[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "proj"), 1, GL_TRUE, &App->camera->GetProjectionMatrix()[0][0]);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);

	// size = 3 float per vertex
	// stride = 0 is equivalent to stride = sizeof(float)*3
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Texture
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * 4 * 3));

	App->texture->LoadImage("..\\Source\\Lenna.png");
	App->texture->LoadTexture(program);

	// 2 triangle to draw = 4 vertices
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void ModuleExercise::RenderBakerhouse(unsigned program)
{
	glUseProgram(program);

	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE, &App->camera->GetModelMatrix()[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_TRUE, &App->camera->GetViewMatrix()[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "proj"), 1, GL_TRUE, &App->camera->GetProjectionMatrix()[0][0]);
	
	model.Load("..\\Source\\baker_house_model\\Baker_house.png", "..\\Source\\baker_house_model\\BakerHouse.fbx", program);
}

void ModuleExercise::RenderModel(unsigned program)
{
	glUseProgram(program);

	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE, &App->camera->GetModelMatrix()[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_TRUE, &App->camera->GetViewMatrix()[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "proj"), 1, GL_TRUE, &App->camera->GetProjectionMatrix()[0][0]);

	model.Draw(program);
}

void ModuleExercise::ModelDropped(const char* file)
{
	imageFile = file;
	fbxFile = file;
	model.Clear();
	model.Load(imageFile, fbxFile, modelProgram);
}

Model ModuleExercise::GetModel()
{
	return model;
}

const char* ModuleExercise::Getfbx()
{
	return fbxFile;
}

std::vector<std::string> ModuleExercise::Getimage()
{
	return model.GetImageName(fbxFile);
}
