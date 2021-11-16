#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleExercise.h"
#include "ModuleDebugDraw.h"
#include "./debug_draw/debugdraw.h"
#include "SDL.h"
#include "GL/glew.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "MathGeoLib.h"

ModuleRender::ModuleRender()
{
}

// Destructor
ModuleRender::~ModuleRender()
{
}

// Called before render is available
bool ModuleRender::Init()
{
	LOG("Creating Renderer context");

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4); // desired version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // we want a double buffer
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); // we want to have a depth buffer with 24 bits
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8); // we want to have a stencil buffer with 8 bits

	context = SDL_GL_CreateContext(App->window->window);
	SDL_GL_MakeCurrent(App->window->window, context);
	
	GLenum err = glewInit();
	// ... check for errors
	LOG("Using Glew %s", glewGetString(GLEW_VERSION));
	// Should be 2.0

	LOG("Vendor: %s", glGetString(GL_VENDOR));
	LOG("Renderer: %s", glGetString(GL_RENDERER));
	LOG("OpenGL version supported %s", glGetString(GL_VERSION));
	LOG("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	glEnable(GL_DEPTH_TEST); // Enable depth test
	glEnable(GL_CULL_FACE); // Enable cull backward faces
	glFrontFace(GL_CCW); // Front faces will be counter clockwise
	glEnable(GL_STENCIL_TEST); // Disable stencil test
	glDisable(GL_SCISSOR_TEST); // Diable scissors test
	//glCullFace(GL_BACK); // By default, back-facing facets are candidates for culling
	//glFrontFace(GL_CCW); // By default, specifies that the orientation of front-facing polygons are counterclockwise 

	/*
	Frustum frustum;
	frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
	frustum.SetViewPlaneDistances(0.1f, 200.0f);
	frustum.SetHorizontalFovAndAspectRatio(DegToRad(90.0f), 1.3f);
	frustum.SetPos(float3(0.0f, 1.0f, -2.0f));
	frustum.SetFront(float3::unitZ);
	frustum.SetUp(float3::unitY);
	float4x4 projectionGL = frustum.ProjectionMatrix().Transposed(); //<-- Important to transpose!
	//Send the frustum projection matrix to OpenGL
	// direct mode would be:
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(*projectionGL.v);

	frustum.SetPos(float3(1.0f, 4.0f, 2.0f));
	//float3x3 rotationMatrix = float3x3::FromEulerXYZ(DegToRad(0.0f), DegToRad(0.0f), DegToRad(-75.0f)); // = some rotation value (or LookAt matrix)
	//frustum.SetFront(rotationMatrix.WorldX());
	//frustum.SetUp(rotationMatrix.WorldY());
	//Send the frustum view matrix to OpenGL
	// direct mode would be:
	float4x4 viewGL = float4x4(frustum.ViewMatrix()).Transposed();
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(*viewGL.v);

	float3x3 rotationDeltaMatrix; // = some rotation delta value
	vec oldFront = frustum.Front().Normalized();
	frustum.SetFront(rotationDeltaMatrix.MulDir(oldFront));
	vec oldUp = frustum.Up().Normalized();
	frustum.SetUp(rotationDeltaMatrix.MulDir(oldUp));
	*/

	return true;
}

update_status ModuleRender::PreUpdate()
{
	int w;
	int h;
	SDL_GetWindowSize(App->window->window, &w, &h);
	glViewport(0, 0, w, h);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRender::Update()
{	
	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	// Rendering grid
	float4x4 view, proj;
	view = App->exercise->view;
	proj = App->exercise->projection;
	
	int w, h;
	SDL_GetWindowSize(App->window->window, &w, &h);
	
	App->debugDraw->Draw(view, proj, w, h);

	// Rendering
	SDL_GL_SwapWindow(App->window->window);

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");

	//Destroy window
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(App->window->window);
	SDL_Quit();

	return true;
}

void ModuleRender::WindowResized(unsigned width, unsigned height)
{
	//glViewport(0, 0, width, height);
}

