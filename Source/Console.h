#pragma once
#include "imgui.h"

class Console
{
public:
	Console();
	~Console();

	void Clear();
	void AddLog(const char* fmt, ...) IM_FMTARGS(2);
	void Draw(const char* title, bool* p_open);

private:
	ImGuiTextBuffer     buff;
	ImGuiTextFilter     filter;
	ImVector<int>       lineOffsets; // Index to lines offset. We maintain this with AddLog() calls.
	bool                autoScroll;  // Keep scrolling if already at the bottom.
};

extern Console* console;
