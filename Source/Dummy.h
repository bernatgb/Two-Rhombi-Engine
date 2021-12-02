#pragma once
#include "Module.h"
#include "Globals.h"

class ModuleDummy : public Module
{
	bool Init()
	{
		CONSOLELOG("Dummy Init!");
		return true;
	}

	bool CleanUp()
	{
		CONSOLELOG("Dummy CleanUp!");
		return true;
	}
};