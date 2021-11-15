#include "Globals.h"
#include "Application.h"
#include "ModuleGUI.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "SDL.h"
#include "GL/glew.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

ModuleGUI::ModuleGUI()
{
}

// Destructor
ModuleGUI::~ModuleGUI()
{
}

// Called before GUI is available
bool ModuleGUI::Init()
{
	LOG("Creating GUI context");

	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->context);
	ImGui_ImplOpenGL3_Init("#version 330");

	return true;
}

void ModuleGUI::Draw()
{
	// Menu
	if (ImGui::BeginMenu("Help"))
	{
		if (ImGui::BeginMenu("File")) {
			ImGui::MenuItem("New");
			ImGui::MenuItem("Open");
			ImGui::MenuItem("Save");
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit")) {
			ImGui::MenuItem("Cut");
			ImGui::MenuItem("Copy");
			ImGui::MenuItem("Paste");
			ImGui::MenuItem("Delete");
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
	// End Menu
	
	/*
	// FPS graph
	char title[25];
	sprintf_s(title, 25, "Framerate % .1f", fps_log[fps_log.size() - 1]);
	ImGui::PlotHistogram("##framerate", &fps_log[0], fps_log.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));
	sprintf_s(title, 25, "Milliseconds % .1f", ms_log[ms_log.size() - 1]);
	ImGui::PlotHistogram("##milliseconds", &ms_log[0], ms_log.size(), 0, title, 0.0f, 40.0f, ImVec2(310, 100));
	// End FPS graph

	// Window options
	if (ImGui::Checkbox("Fullscreen", &fullsceen))
		App->window->SetFullSreen(fullscreen);

	ImGui::SameLine();
	if (ImGui::Checkbox("Resizable, &resizable"))
		App->window->SetResizable(resizable);
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip("Restart to apply");
	// End Window options
	*/
}

update_status ModuleGUI::PreUpdate()
{
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	if (demo)
		ImGui::ShowDemoWindow(&demo);

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleGUI::Update()
{
	Draw();
	return UPDATE_CONTINUE;
}

update_status ModuleGUI::PostUpdate()
{
	// Rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleGUI::CleanUp()
{
	LOG("Destroying GUI");

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	return true;
}
