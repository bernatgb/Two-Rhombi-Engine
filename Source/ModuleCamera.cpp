#include "Globals.h"
#include "ModuleCamera.h"
#include "SDL.h"
#include "MathGeoLib.h"

ModuleCamera::ModuleCamera()
{
}

// Destructor
ModuleCamera::~ModuleCamera()
{
}

bool ModuleCamera::Init()
{
	frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
	frustum.SetViewPlaneDistances(0.1f, 200.0f);
	frustum.SetHorizontalFovAndAspectRatio(DegToRad(90.0f), 1.3f);
	frustum.SetPos(float3(0.0f, 1.0f, -5.0f));
	frustum.SetFront(float3::unitZ);
	frustum.SetUp(float3::unitY);

	model = float4x4::identity;  //float4x4::FromTRS(float3(0.0f, 0.0f, 0.0f), float4x4::RotateX(0), float3(1.0f, 1.0f, 1.0f));
	view = float4x4(frustum.ViewMatrix());
	projection = frustum.ProjectionMatrix();

	return true;
}

update_status ModuleCamera::Update()
{	
	return UPDATE_CONTINUE;
}

bool ModuleCamera::CleanUp()
{
	return true;
}

void ModuleCamera::MoveCamera(char direction)
{
	float3 newPos = frustum.Pos();

	switch (direction)
	{
	// Go up/down in absolute values
	case 'q':
		newPos += float3::unitY * 0.05f * speed;
		break;

	case 'e':
		newPos -= float3::unitY * 0.05f * speed;
		break;

	// Move forward and backward relative to camera orientation
	case 'w':
		newPos += frustum.Front() * 0.05f * speed;
		break;

	case 's':
		newPos -= frustum.Front() * 0.05f * speed;
		break; 
		
	// Move left and right relative to camera orientation
	case 'a':
		newPos -= frustum.WorldRight() * 0.05f * speed;
		break;

	case 'd':
		newPos += frustum.WorldRight() * 0.05f * speed;
		break;
	}
	
	frustum.SetPos(newPos);
	view = float4x4(frustum.ViewMatrix());
}

void ModuleCamera::RotateCamera(char rotation)
{
	float3x3 newOrientation;

	switch (rotation)
	{
	// Have up/down arrow keys rotate the camera’s Pitch (X axis)
	case 'u':
		newOrientation = float3x3::RotateX(-0.05f);
		frustum.SetFront(newOrientation.MulDir(frustum.Front().Normalized()));
		frustum.SetUp(newOrientation.MulDir(frustum.Up().Normalized()));
		break;

	case 'd':
		newOrientation = float3x3::RotateX(0.05f);
		frustum.SetFront(newOrientation.MulDir(frustum.Front().Normalized()));
		frustum.SetUp(newOrientation.MulDir(frustum.Up().Normalized()));
		break;

	// Same for left/right affecting camera’s Yaw (Y axis)
	case 'l':
		newOrientation = float3x3::RotateY(-0.05f);
		frustum.SetFront(frustum.Front() * newOrientation);
		break;

	case 'r':
		newOrientation = float3x3::RotateY(0.05f);
		frustum.SetFront(frustum.Front() * newOrientation);
		break;
	}

	view = float4x4(frustum.ViewMatrix());
	projection = frustum.ProjectionMatrix();
}

void ModuleCamera::DoubleSpeed(bool shiftPressed)
{
	if (shiftPressed) speed = 2.0f;
	else speed = 1.0f;
}

void ModuleCamera::TripleSpeed(bool shiftPressed)
{
	if (shiftPressed) speed = 3.0f;
	else speed = 1.0f;
}

void ModuleCamera::LookAt(float3 position)
{
	//float3 targetDirection = position - frustum.Pos();
	//float3x3 toLookAt = float3x3::LookAt(frustum.Front(), targetDirection.Normalized(), frustum.Up(), float3::unitY);
	
	//float3 targetDirection = frustum.Pos() - position.Normalized();
	//float3x3 toLookAt = float3x3::LookAt(frustum.Front(), targetDirection, frustum.Up(), float3::unitY);
	
	//frustum.SetFront(toLookAt.MulDir(frustum.Front().Normalized()));
	//frustum.SetUp(toLookAt.MulDir(frustum.Up().Normalized()));

	float3 targetDirection = position - frustum.Pos();
	
	float3 front = targetDirection.Normalized();
	frustum.SetFront(front);
	
	float3 right = Cross(float3::unitY, front);
	float3 up = Cross(front, right.Normalized());
	frustum.SetUp(up.Normalized());
	
	view = float4x4(frustum.ViewMatrix());
	projection = frustum.ProjectionMatrix();
}

void ModuleCamera::WindowResized(float aspectRatio, bool horizontal)
{
	if (horizontal)
		frustum.SetHorizontalFovAndAspectRatio(frustum.HorizontalFov(), aspectRatio);
	else
		frustum.SetVerticalFovAndAspectRatio(frustum.VerticalFov(), aspectRatio);

	projection = frustum.ProjectionMatrix();
}
