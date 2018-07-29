#include "EngineUI.h"

void EngineUI::CreateUIContext(GLFWwindow* window)
{
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();
}

void EngineUI::TerminateUIContext()
{
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
}

void EngineUI::DrawDefaultScreen()
{
	ImGui_ImplGlfwGL3_NewFrame();

	ImGui::BeginMainMenuBar();
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::MenuItem("New");
			ImGui::MenuItem("Open");
			ImGui::MenuItem("Save");
			ImGui::MenuItem("Save As");
			ImGui::MenuItem("Build");
			ImGui::MenuItem("Exit");
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			ImGui::MenuItem("Undo");
			ImGui::MenuItem("Redo");
			ImGui::MenuItem("Cut");
			ImGui::MenuItem("Copy");
			ImGui::MenuItem("Paste");
			ImGui::MenuItem("Delete");
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Components"))
		{
			ImGui::MenuItem("Transform");
			ImGui::MenuItem("Rigidbody");
			ImGui::MenuItem("Custom");
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Windows"))
		{
			ImGui::MenuItem("Hierarchy");
			ImGui::MenuItem("Inspector");
			ImGui::MenuItem("Console");
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{
			ImGui::MenuItem("Help");
			ImGui::MenuItem("About React3D");
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}