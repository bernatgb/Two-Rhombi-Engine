#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCamera.h"
#include "ModuleExercise.h"
#include "SDL/include/SDL.h"
#include "MathGeoLib.h"

ModuleInput::ModuleInput()
{}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
	CONSOLELOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		CONSOLELOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::Update()
{
    SDL_Event sdlEvent;

    while (SDL_PollEvent(&sdlEvent) != 0)
    {
        switch (sdlEvent.type)
        {
            case SDL_QUIT:
                return UPDATE_STOP;
            case SDL_WINDOWEVENT:
                if (sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED || sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                    App->renderer->WindowResized(sdlEvent.window.data1, sdlEvent.window.data2);
                break;
			case SDL_MOUSEWHEEL: // Mouse wheel rotation
				if (sdlEvent.wheel.y > 0) // move forwards
				{
					App->camera->MoveCamera('w');
				}
				else if (sdlEvent.wheel.y < 0) // move backwards
				{
					App->camera->MoveCamera('s');
				}
				break;
			case SDL_MOUSEMOTION:
				if (mouseRButtonDown && xyUpdated)
				{
					float xDiff = math::Abs(x - sdlEvent.button.x);
					float yDiff = math::Abs(y - sdlEvent.button.y);
					if (xDiff >= yDiff)
					{
						if (x > sdlEvent.button.x)
						{
							App->camera->RotateCamera('r');
							x = sdlEvent.button.x;
						}
						else if (x < sdlEvent.button.x)
						{
							App->camera->RotateCamera('l');
							x = sdlEvent.button.x;
						}
					}
					else // xDiff < yDiff
					{
						if (y > sdlEvent.button.y)
						{
							App->camera->RotateCamera('d');
							y = sdlEvent.button.y;
						}
						else if (y < sdlEvent.button.y)
						{
							App->camera->RotateCamera('u');
							y = sdlEvent.button.y;
						}
					}
				}
				break;
			case SDL_DROPFILE:
				CONSOLELOG("New model dropped.");
				App->exercise->ModelDropped(sdlEvent.drop.file);
				break;

        }
    }

    keyboard = SDL_GetKeyboardState(NULL);
    
    if (keyboard[SDL_SCANCODE_ESCAPE]) {
        CONSOLELOG("<ESCAPE> is pressed.");
        return UPDATE_STOP;
    }
	// Go up/down in absolute values
	if (keyboard[SDL_SCANCODE_Q]) {
		CONSOLELOG("<Q> is pressed.");
		App->camera->MoveCamera('q');
	}
	else if (keyboard[SDL_SCANCODE_E]) {
		CONSOLELOG("<E> is pressed.");
		App->camera->MoveCamera('e');
	}

	// Move forward and backward relative to camera orientation
	else if (keyboard[SDL_SCANCODE_W]) {
		CONSOLELOG("<W> is pressed.");
		App->camera->MoveCamera('w');
	}
	else if (keyboard[SDL_SCANCODE_S]) {
		CONSOLELOG("<S> is pressed.");
		App->camera->MoveCamera('s');
	}

	// Move left and right relative to camera orientation
	else if (keyboard[SDL_SCANCODE_A]) {
		CONSOLELOG("<A> is pressed.");
		App->camera->MoveCamera('a');
	}
	else if (keyboard[SDL_SCANCODE_D]) {
		CONSOLELOG("<D> is pressed.");
		App->camera->MoveCamera('d');
	}

	// Have up/down arrow keys rotate the camera’s Pitch (Y axis)
	else if (keyboard[SDL_SCANCODE_UP]) {
		CONSOLELOG("<UP> is pressed.");
		App->camera->RotateCamera('u');
	}
	else if (keyboard[SDL_SCANCODE_DOWN]) {
		CONSOLELOG("<DOWN> is pressed.");
		App->camera->RotateCamera('d');
	}

	// Same for left/right affecting camera’s Yaw (Z axis)
	else if (keyboard[SDL_SCANCODE_LEFT]) {
		CONSOLELOG("<LEFT> is pressed.");
		App->camera->RotateCamera('l');
	}
	else if (keyboard[SDL_SCANCODE_RIGHT]) {
		CONSOLELOG("<RIGHT> is pressed.");
		App->camera->RotateCamera('r');
	}

	// Focus the camera around the geometry
	else if (keyboard[SDL_SCANCODE_F]) {
		CONSOLELOG("<F> is pressed.");
		Model model = App->exercise->GetModel();
		float3 toLookAt = model.GetPos();
		App->camera->LookAt(toLookAt);
	}

	// Orbit the object
	else if (keyboard[SDL_SCANCODE_LALT] || keyboard[SDL_SCANCODE_RALT]) {
		CONSOLELOG("<ALT> is pressed.");
		Model model = App->exercise->GetModel();
		float3 modelPos = model.GetPos();
		App->camera->OrbitCamera(modelPos);
	}

	// Reset the camera
	else if (keyboard[SDL_SCANCODE_R]) {
		CONSOLELOG("<R> is pressed.");
		App->camera->ResetCamera();
	}

	// Have the camera speed double/triple if SHIFT is being pressed
	while (keyboard[SDL_SCANCODE_LSHIFT]) {
		CONSOLELOG("<LSHIFT> is pressed.");
		lshiftWasPressed = true;
		App->camera->DoubleSpeed(true);
	}
	if (lshiftWasPressed)
	{
		App->camera->DoubleSpeed(false);
		lshiftWasPressed = false;
	}

	while (keyboard[SDL_SCANCODE_RSHIFT]) {
		CONSOLELOG("<RSHIFT> is pressed.");
		rshiftWasPressed = true;
		App->camera->TripleSpeed(true);
	}
	if (rshiftWasPressed)
	{
		App->camera->TripleSpeed(false);
		rshiftWasPressed = false;
	}
	
	// Mouse rotation	
	if (mouseRButtonDown && sdlEvent.type == SDL_MOUSEBUTTONUP && sdlEvent.button.button == SDL_BUTTON_RIGHT)
	{
		mouseRButtonDown = false;
		xyUpdated = false;
	}
	if (!mouseRButtonDown && sdlEvent.type == SDL_MOUSEBUTTONDOWN && sdlEvent.button.button == SDL_BUTTON_RIGHT)
	{
		mouseRButtonDown = true;
		x = sdlEvent.button.x;
		y = sdlEvent.button.y;
		xyUpdated = true;
	}


    return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	CONSOLELOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}
