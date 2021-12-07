#include "Globals.h"
#include "Application.h"
#include "ModuleGUI.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleCamera.h"
#include "ModuleExercise.h"
#include "ModuleDebugDraw.h"
#include "Timer.h"
#include "Console.h"
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
	CONSOLELOG("Creating GUI context.");

	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->context);
	ImGui_ImplOpenGL3_Init("#version 330");

	fps_log.resize(25);
	ms_log.resize(25);

	hardware.n_cpu = SDL_GetCPUCount();
	hardware.ram_gb = SDL_GetSystemRAM() / 1024.0f;

	hardware.gpu = (unsigned char*)glGetString(GL_RENDERER);
	hardware.gpu_brand = (unsigned char*)glGetString(GL_VENDOR);
	glGetIntegerv(GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &hardware.vram_budget);
	glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &hardware.vram_free);

	SDL_GetVersion(&software.sdl_version);
	software.gl_version = (char*)glGetString(GL_VERSION);

	regulateFramerate = timer.GetRegulateFramerate();
	doubleFramerate = timer.GetDoubleFramerate();
	notDoubleFramerate = !doubleFramerate;

	timer.Start();

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
	update_status draw = Draw();

	if (about)
		DrawAbout(&about);

	if (show_app_log)
		console->Draw("Console", &show_app_log);

	if (config)
		DrawConfig(&config);
	
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
	CONSOLELOG("Destroying GUI");

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
		if (ImGui::BeginMenu("Menu")) {
			if (ImGui::MenuItem("Quit"))
			{
				quit = true;
			}
			if (ImGui::MenuItem("Visit Github page"))
			{
				ShellExecute(NULL, "open", "https://github.com/bernatgb/Two-Rhombi-Engine", NULL, NULL, SW_SHOWNORMAL);
			}
			if (ImGui::MenuItem("About"))
			{
				about = !about;
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Controllers")) {
			if (ImGui::MenuItem("Console"))
			{
				show_app_log = !show_app_log;
			}
			if (ImGui::MenuItem("Configuration"))
			{
				config = !config;
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
	// End Menu

	if (quit)
		return UPDATE_STOP;
	else
		return UPDATE_CONTINUE;
}

void ModuleGUI::DrawAbout(bool* about)
{
	if (!ImGui::Begin("About", about))
	{
		ImGui::End();
		return;
	}

	ImGui::Text("Engine name: Two Rhombi Engine");
	ImGui::Text("Description: Engine made in UPC Master");
	ImGui::Text("Author: Bernat Güell");
	ImGui::Separator();
	ImGui::Text("Libraries:");
	ImGui::BulletText("DevIL");
	ImGui::BulletText("GLEW");
	ImGui::BulletText("ImGui");
	ImGui::BulletText("MathGeoLib");
	ImGui::BulletText("SDL");

	ImGui::End();
}

void ModuleGUI::DrawConfig(bool* config)
{
	if (!ImGui::Begin("Configuration", config))
	{
		ImGui::End();
		return;
	}

	// Configuration
	if (ImGui::Begin("Configuration"))
	{
		if (ImGui::CollapsingHeader("Application"))
		{
			fps_log.erase(fps_log.begin());
			fps_log.push_back(timer.FrameInfo());
			ms_log.erase(ms_log.begin());
			ms_log.push_back(timer.ReadMS());
			// FPS graph
			char title[25];
			sprintf_s(title, 25, "Frame rate: %.1f", fps_log[fps_log.size() - 1]);
			ImGui::PlotHistogram("##framerate", &fps_log[0], fps_log.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));
			//sprintf_s(title, 25, "Milliseconds % .1f", ms_log[ms_log.size() - 1]);
			//ImGui::PlotHistogram("##milliseconds", &ms_log[0], ms_log.size(), 0, title, 0.0f, 40.0f, ImVec2(310, 100));
			// End FPS graph

			ImGui::Separator();

			if (ImGui::Checkbox("Regulate frame rate", &regulateFramerate))
				timer.SetRegulateFramerate();

			if (ImGui::Checkbox("30 FPS", &notDoubleFramerate))
			{
				timer.SetDoubleFramerate();
				doubleFramerate = !doubleFramerate;
			}

			ImGui::SameLine();

			if (ImGui::Checkbox("60 FPS", &doubleFramerate))
			{
				timer.SetDoubleFramerate();
				notDoubleFramerate = !notDoubleFramerate;
			}
		}

		if (ImGui::CollapsingHeader("Window"))
		{
			// Window options
			if (ImGui::Checkbox("Fullscreen", &fullscreen))
				App->window->SetFullscreen(fullscreen);

			ImGui::SameLine();

			if (ImGui::Checkbox("Resizable", &resizable))
				App->window->SetResizable(resizable);

			int screenWidth = App->window->GetWidth();
			if (ImGui::SliderInt("Screen Width", &screenWidth, 160, 1600, "%d", 0))
			{
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Set Windows as resizable before");

				if (resizable)
					App->window->SetWidth(screenWidth);
			}
			int screenHeight = App->window->GetHeight();
			if (ImGui::SliderInt("Screen Height", &screenHeight, 90, 900, "%d", 0))
			{
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Set Windows as resizable before");

				if (resizable)
					App->window->SetHeight(screenHeight);
			}
			// End Window options
		}

		if (ImGui::CollapsingHeader("Debug draw"))
		{
			bool enabled = App->debugDraw->GetDebugDrawEnabled();
			if (ImGui::Checkbox("Enable debug draw", &enabled))
				App->debugDraw->SetDebugDrawEnabled();
		}

		if (ImGui::CollapsingHeader("Camera"))
		{
			float3x3 transform = App->camera->GetTransform();
			ImGui::Text("Position: (%f,%f,%f)", transform.Col(0).x, transform.Col(0).y, transform.Col(0).z);
			ImGui::Text("Front: (%f,%f,%f)", transform.Col(1).x, transform.Col(1).y, transform.Col(1).z);
			ImGui::Text("Up: (%f,%f,%f)", transform.Col(2).x, transform.Col(2).y, transform.Col(2).z);
			ImGui::Text("Camera speed: %f", App->camera->GetCameraSpeed());
		}

		if (ImGui::CollapsingHeader("Model"))
		{
			const char* fbx = App->exercise->Getfbx();
			ImGui::Text("fbx file name: %s", fbx);
			Model model = App->exercise->GetModel();
			if (ImGui::TreeNode("Transform"))
			{
				ImGui::BulletText("Postion: (%f, %f, %f)", model.GetPosition().x, model.GetPosition().y, model.GetPosition().z);

				ImGui::BulletText("Rotation Matrix: (%f, %f, %f)", model.GetRotation()[0][0], model.GetRotation()[0][1], model.GetRotation()[0][2]);
				ImGui::Text("					(%f, %f, %f)", model.GetRotation()[1][0], model.GetRotation()[1][1], model.GetRotation()[1][2]);
				ImGui::Text("					(%f, %f, %f)", model.GetRotation()[2][0], model.GetRotation()[2][1], model.GetRotation()[2][2]);

				ImGui::BulletText("Scale: (%f, %f, %f)", model.GetScale().x, model.GetScale().y, model.GetScale().z);
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("Meshes & textures"))
			{
				std::vector<int> faces = model.GetFaces();
				std::vector<std::string> images = model.GetImagesNames();
				for (int i = 0; i < faces.size(); ++i)
				{
					ImGui::BulletText("Mesh %i:", i + 1); 
					ImGui::Text("	has %i triangles", faces[i]);
					ImGui::Text("	its texture image name is %s", images[i].c_str());
				}
				ImGui::TreePop();

			}
		}


		if (ImGui::CollapsingHeader("Hardware & Software"))
		{
			if (ImGui::TreeNode("Hardware"))
			{
				static const float vram_budget_mb = hardware.vram_budget / 1024.0f;
				glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &hardware.vram_free);
				float vram_free_mb = hardware.vram_free / 1024.0f;
				float vram_usage_mb = vram_budget_mb - vram_free_mb;

				ImGui::Text("CPUs: %d", hardware.n_cpu);
				ImGui::Text("System RAM: %.1f Gb", hardware.ram_gb);
				ImGui::Separator();
				ImGui::Text("GPU: %s", hardware.gpu);
				ImGui::Text("Brand: %s", hardware.gpu_brand);
				ImGui::Text("VRAM Budget: %.1f Mb", vram_budget_mb);
				ImGui::Text("Vram Usage:  %.1f Mb", vram_usage_mb);
				ImGui::Text("Vram Avaliable:  %.1f Mb", vram_free_mb);
				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Software"))
			{
				ImGui::Text("SDL Version: %d.%d.%d", software.sdl_version.major,
					software.sdl_version.minor, software.sdl_version.patch);
				ImGui::Text("OpenGL Version: %s", software.gl_version);
				ImGui::TreePop();
			}

		}	
		ImGui::End();	
	}
	// End Configuration
	
	ImGui::End();
}
