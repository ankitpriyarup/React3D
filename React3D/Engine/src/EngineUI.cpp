#include "EngineUI.h"

ImFont* EngineUI::defaultFont;
ImFont* EngineUI::curFont;

void EngineUI::CreateUIContext(GLFWwindow* window)
{
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();

	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("res/DroidSans.ttf", 16.0f);
	unsigned char* pixels;
	int width, height;
	io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);
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
		if (ImGui::BeginMenu("View"))
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