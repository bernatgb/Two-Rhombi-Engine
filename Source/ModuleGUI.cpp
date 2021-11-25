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

	//ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->context);
	ImGui_ImplOpenGL3_Init("#version 330");

	fps_log.resize(25);
	ms_log.resize(25);

	SDL_GetVersion(&hardware.sdl_version);
	hardware.n_cpu = SDL_GetCPUCount();
	hardware.ram_gb = SDL_GetSystemRAM() / 1024.0f;

	hardware.gpu = (unsigned char*)glGetString(GL_RENDERER);
	hardware.gpu_brand = (unsigned char*)glGetString(GL_VENDOR);
	glGetIntegerv(GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &hardware.vram_budget);
	glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &hardware.vram_free);

	return true;
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
	update_status draw =	Draw();

	// Rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	return draw;
}

update_status ModuleGUI::PostUpdate()
{
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

update_status ModuleGUI::Draw()
{
	bool quit = false;
	// Menu
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("Quit"))
			{
				quit = true;
			}
		ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit")) {
			if (ImGui::MenuItem("Cut")) {}
			if (ImGui::MenuItem("Copy")) {}
			if (ImGui::MenuItem("Paste")) {}
			if (ImGui::MenuItem("Delete")) {}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
	// End Menu

	// Configuration
	if (ImGui::CollapsingHeader("Application"))
	{
		// FPS graph
		char title[25];
		sprintf_s(title, 25, "Framerate % .1f", fps_log[fps_log.size() - 1]);
		ImGui::PlotHistogram("##framerate", &fps_log[0], fps_log.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));
		sprintf_s(title, 25, "Milliseconds % .1f", ms_log[ms_log.size() - 1]);
		ImGui::PlotHistogram("##milliseconds", &ms_log[0], ms_log.size(), 0, title, 0.0f, 40.0f, ImVec2(310, 100));
		// End FPS graph
	}

	if (ImGui::CollapsingHeader("Window"))
	{
		/*
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

	if (ImGui::CollapsingHeader("Hardware"))
	{
		static SDL_version version;
		static const float vram_budget_mb = hardware.vram_budget / 1024.0f;
		glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &hardware.vram_free);
		float vram_free_mb = hardware.vram_free / 1024.0f;
		float vram_usage_mb = vram_budget_mb - vram_free_mb;

		ImGui::Text("SDL Version: %d.%d.%d", hardware.sdl_version.major,
			hardware.sdl_version.minor, hardware.sdl_version.patch);
		ImGui::Separator();
		ImGui::Text("CPUs: %d", hardware.n_cpu);
		ImGui::Text("System RAM: %.1f Gb", hardware.ram_gb);
		ImGui::Separator();
		ImGui::Text("GPU: %s", hardware.gpu);
		ImGui::Text("Brand: %s", hardware.gpu_brand);
		ImGui::Text("VRAM Budget: %.1f Mb", vram_budget_mb);
		ImGui::Text("Vram Usage:  %.1f Mb", vram_usage_mb);
		ImGui::Text("Vram Avaliable:  %.1f Mb", vram_free_mb);
	}

	if (ImGui::CollapsingHeader("About"))
	{
		ImGui::Text("Engine name: Two Rhombi Engine");
		ImGui::Text("Description: Engine made in UPC Master");
		ImGui::Text("Author: Bernat Güell");
		ImGui::Separator();
		ImGui::Text("Libraries:");
		ImGui::Text("	*DevIL");
		ImGui::Text("	*GLEW");
		ImGui::Text("	*ImGui");
		ImGui::Text("	*MathGeoLib");
		ImGui::Text("	*SDL");
	}

	// End Configuration

	if (quit)
		return UPDATE_STOP;
	else
		return UPDATE_CONTINUE;
}
