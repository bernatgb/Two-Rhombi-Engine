#pragma once
#include "Module.h"
#include "Globals.h"
#include "MathGeoLib.h"

class ModuleCamera : public Module
{
public:
	ModuleCamera();
	~ModuleCamera();

	bool Init();
	update_status Update();
	bool CleanUp();

	void MoveCamera(char direction);
	void RotateCamera(char rotarion);
	void OrbitCamera(float3 position);
	void DoubleSpeed(bool shiftPressed);
	void TripleSpeed(bool shiftPressed);
	void LookAt(float3 position);
	void WindowResized(float aspectRatio, bool horizontal);

	float4x4 model, view, projection;
	

private:
	Frustum frustum;
	float speed = 1.0f;
};