#pragma once
#include "GUI_Window.h"
#include "TextEditor.h"
#include ""

class WindowScript : public GUI_Window
{
public:
	WindowScript(string name, bool startEnabled = false, ImGuiWindowFlags flags = ImGuiWindowFlags_None);

	void Update();

	void CreationMenu();
	void SetTextEditor();
	void SetFile(String file);
	void ScriptTextEditor();

public:
	TextEditor text_editor;
	std::string file_to_edit;
	std::string file_name;

};

