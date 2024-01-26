#define _CRT_SECURE_NO_WARNINGS

#include "WindowScript.h"

WindowScript::WindowScript(string name, bool startEnabled, ImGuiWindowFlags flags) : GUI_Window(name, startEnabled, flags) {
	auto lang = TextEditor::LanguageDefinition::CPlusPlus();

	// set your own known preprocessor symbols...
	{
		static const char* ppnames[] = { "NULL", "ALIEN_ENGINE_API", "ALIEN_INIT_DATA", "ALIEN_DESTROY_DATA", "ALIEN_INIT_HEADER",
			"ALIEN_END_HEADER", "ALIENENGINESCRIPTS_EXPORTS"
		};
		// ... and their corresponding values
		static const char* ppvalues[] = {
			"#define NULL 0", "#define ALIEN_ENGINE_API __declspec(dllexport)", "#define ALIEN_INIT_DATA ALIEN_ENGINE_API", "#define ALIEN_DESTROY_DATA ALIEN_ENGINE_API",
			"#define ALIEN_INIT_HEADER extern 'C' {", "#define ALIEN_END_HEADER }", "#define ALIENENGINESCRIPTS_EXPORTS",
		};

		for (int i = 0; i < sizeof(ppnames) / sizeof(ppnames[0]); ++i)
		{
			TextEditor::Identifier id;
			id.mDeclaration = ppvalues[i];
			lang.mPreprocIdentifiers.insert(std::make_pair(std::string(ppnames[i]), id));
		}
	}

	// set your own identifiers
	{
		static const char* identifiers[] = {
			"u64", "uint", "GameObject", "Alien", "Input"
		};
		static const char* idecls[] =
		{
			"typedef unsigned long long u64", "typedef unsigned int uint", "none", "none", "none"
		};
		for (int i = 0; i < sizeof(identifiers) / sizeof(identifiers[0]); ++i)
		{
			TextEditor::Identifier id;
			id.mDeclaration = std::string(idecls[i]);
			lang.mIdentifiers.insert(std::make_pair(std::string(identifiers[i]), id));
		}
	}

	text_editor.SetLanguageDefinition(lang);

	SetFile("DGameEngine/DScripts.h");
}

void WindowScript::Update() {
	CreationMenu();
}

void WindowScript::CreationMenu() {
	static int type = 0;
	static char _name[MAX_PATH] = "Data Name";
	static bool _export = true;
	bool change = true;

	ImGui::OpenPopup("Create New Script");
	ImGui::SetNextWindowSize({ 320,155 });
	if (ImGui::BeginPopupModal("Create New Script", &change, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove)) {
		ImGui::PushItemWidth(135);
		ImGui::SetCursorPosX(28);
		ImGui::Combo("Select Script Type", &type, "Script Type\0Class\0Struct\0");

		ImGui::Spacing();
		ImGui::SetCursorPosX(15);
		ImGui::InputText("Name", _name, MAX_PATH, ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_EnterReturnsTrue);
		ImGui::SameLine();
		ImGui::Checkbox("Export Script", &_export);
		ImGui::Spacing();
		ImGui::SetCursorPosX(42);
		ImGui::Text("Header and Cpp will be genereated,");
		ImGui::SetCursorPosX(33);
		ImGui::Text("just add them as an existing element.");
		ImGui::Spacing();
		ImGui::SetCursorPosX(90);
		if (ImGui::Button("Create Script", { 130,25 })) {
			if (std::string(_name).find(" ") == std::string::npos && type != 0) {
				//CreateScriptFile(type, _export, _name);
				type = 0;
				strcpy(_name, "Data Name");
				_export = true;
				change = false;
			}
		}

		ImGui::EndPopup();
	}
	else {
		type = 0;
		strcpy(_name, "Data Name");
		_export = true;
	}
}

void WindowScript::SetTextEditor() {

}

void WindowScript::SetFile(String* file)
{
	file_to_edit = std::string(file);
	file_name = App->file_system->GetBaseFileNameWithExtension(file);

	std::ifstream t(file);
	if (t.good()) {
		std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
		text_editor.SetText(str);
	}
}

void WindowScript::ScriptTextEditor() {

	bool change = true;

	ImGui::Begin("Script Editor", &change, ImGuiWindowFlags_MenuBar);

	auto cpos = text_editor.GetCursorPosition();
	ImGui::SetWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::BeginMenu("Open")) {
				/*if (all_scripts_files.empty()) {
					GetAllFiles();
				}
				std::vector<std::string>::iterator item = all_scripts_files.begin();
				for (; item != all_scripts_files.end(); ++item) {
					std::string extension;
					App->file_system->SplitFilePath((*item).data(), nullptr, nullptr, &extension);
					if (App->StringCmp(extension.data(), "cpp") || App->StringCmp(extension.data(), "h")) {
						if (ImGui::MenuItem((*item).data(), nullptr, nullptr, !App->StringCmp((*item).data(), file_name.data()))) {
							SetFile(std::string(HEADER_SCRIPTS_FILE + (*item)).data());
						}
					}
				}*/

				ImGui::EndMenu();
			}
			/*else if (!all_scripts_files.empty()) {
				all_scripts_files.clear();
			}*/

			if (ImGui::MenuItem("Save"))
			{
				std::string to_save = text_editor.GetText();
				//App->file_system->Save(file_to_edit.data(), to_save.data(), to_save.size());
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			bool ro = text_editor.IsReadOnly();
			if (ImGui::MenuItem("Read-only mode", nullptr, &ro))
				text_editor.SetReadOnly(ro);
			ImGui::Separator();

			if (ImGui::MenuItem("Undo", "ALT-Backspace", nullptr, !ro && text_editor.CanUndo()))
				text_editor.Undo();
			if (ImGui::MenuItem("Redo", "Ctrl-Y", nullptr, !ro && text_editor.CanRedo()))
				text_editor.Redo();

			ImGui::Separator();

			if (ImGui::MenuItem("Copy", "Ctrl-C", nullptr, text_editor.HasSelection()))
				text_editor.Copy();
			if (ImGui::MenuItem("Cut", "Ctrl-X", nullptr, !ro && text_editor.HasSelection()))
				text_editor.Cut();
			if (ImGui::MenuItem("Delete", "Del", nullptr, !ro && text_editor.HasSelection()))
				text_editor.Delete();
			if (ImGui::MenuItem("Paste", "Ctrl-V", nullptr, !ro && ImGui::GetClipboardText() != nullptr))
				text_editor.Paste();

			ImGui::Separator();

			if (ImGui::MenuItem("Select all", nullptr, nullptr))
				text_editor.SetSelection(TextEditor::Coordinates(), TextEditor::Coordinates(text_editor.GetTotalLines(), 0));

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("View"))
		{
			if (ImGui::MenuItem("Dark palette"))
				text_editor.SetPalette(TextEditor::GetDarkPalette());
			if (ImGui::MenuItem("Light palette"))
				text_editor.SetPalette(TextEditor::GetLightPalette());
			if (ImGui::MenuItem("Retro blue palette"))
				text_editor.SetPalette(TextEditor::GetRetroBluePalette());
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}


	/*ImGui::Text("%6d/%-6d %6d lines  | %s | %s | %s | %s", cpos.mLine + 1, cpos.mColumn + 1, text_editor.GetTotalLines(),
		text_editor.IsOverwrite() ? "Ovr" : "Ins",
		text_editor.CanUndo() ? "*" : " " 
		text_editor.GetLanguageDefinition().mName.c_str(), file_name.data());

	text_editor.Render("TextEditor");*/

	//is_focused = ImGui::IsWindowFocused(ImGuiFocusedFlags_::ImGuiFocusedFlags_ChildWindows);

	ImGui::End();

}