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
	void ResetCamera();
	float4x4 GetModelMatrix();
	float4x4 GetViewMatrix();
	float4x4 GetProjectionMatrix();
	float3x3 GetTransform();
	float GetCameraSpeed();
	void SetCamera(float3 max, float3 min);

private:
	Frustum frustum;
	float4x4 model, view, projection;
	float speed = 1.0f;
};