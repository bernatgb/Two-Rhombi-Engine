#pragma once
#include <windows.h>
#include <stdio.h>
#include "Console.h"

//#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

#define LOG(format, ...) console->AddLog(format, __VA_ARGS__);

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Configuration -----------
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define FULLSCREEN false
#define RESIZABLE true
#define VSYNC true
#define TITLE "Super Awesome Engine"