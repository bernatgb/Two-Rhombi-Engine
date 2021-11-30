#include "Console.h"
#include "imgui.h"
//#include <stdio.h>
//#include <debugapi.h>

Console::Console()
{
	autoScroll = true;
	Clear();
}

Console::~Console()
{
	Clear();
}


void Console::Clear()
{
	buff.clear();
	lineOffsets.clear();
	lineOffsets.push_back(0);
}

void Console::AddLog(const char* fmt, ...) IM_FMTARGS(2)
{
	int old_size = buff.size();
	va_list args;
	va_start(args, fmt);
	buff.appendfv(fmt, args);
	va_end(args);
	for (int new_size = buff.size(); old_size <= new_size; old_size++)
		if (buff[old_size] == '\0')
			lineOffsets.push_back(old_size); 
}

void Console::Draw(const char* title, bool* p_open)
{
	if (!ImGui::Begin(title, p_open))
	{
		ImGui::End();
		return;
	}

	// Options menu
	if (ImGui::BeginPopup("Options"))
	{
		ImGui::Checkbox("Auto-scroll", &autoScroll);
		ImGui::EndPopup();
	}

	// Main window
	if (ImGui::Button("Options"))
		ImGui::OpenPopup("Options");
	ImGui::SameLine();
	bool clear = ImGui::Button("Clear");
	ImGui::SameLine();
	bool copy = ImGui::Button("Copy");
	ImGui::SameLine();
	filter.Draw("Filter", -100.0f);

	ImGui::Separator();
	ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

	if (clear)
		Clear();
	if (copy)
		ImGui::LogToClipboard();

	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
	const char* buf = buff.begin();
	const char* buf_end = buff.end();
	if (filter.IsActive())
	{
		for (int line_no = 0; line_no < lineOffsets.Size; line_no++)
		{
			const char* line_start = buf + lineOffsets[line_no];
			const char* line_end = (line_no + 1 < lineOffsets.Size) ? (buf + lineOffsets[line_no + 1] - 1) : buf_end;
			if (filter.PassFilter(line_start, line_end))
				ImGui::TextUnformatted(line_start, line_end);
		}
	}
	else
	{
		ImGuiListClipper clipper;
		clipper.Begin(lineOffsets.Size);
		while (clipper.Step())
		{
			for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
			{
				const char* line_start = buf + lineOffsets[line_no];
				const char* line_end = (line_no + 1 < lineOffsets.Size) ? (buf + lineOffsets[line_no + 1] - 1) : buf_end;
				ImGui::TextUnformatted(line_start, line_end);
			}
		}
		clipper.End();
	}
	ImGui::PopStyleVar();

	if (autoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
		ImGui::SetScrollHereY(1.0f);

	ImGui::EndChild();
	ImGui::End();
}
