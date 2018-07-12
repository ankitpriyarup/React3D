#include "EngineResources.h"
#include "Window.h"
#include "scene/Scene.h"
#include "scene/TestClearColor.h"
#include "Renderer.h"

scene::TestClearColor* test;
Renderer* renderer;
GLFWwindow* window;

void load()
{
	test = new scene::TestClearColor;
	renderer = new Renderer;

	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();
}

void refresh()
{
	test->OnUpdate(0.0f);
	test->OnRender();

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

	ImGui::BeginChild("Scrolling");
	for (int n = 0; n < 50; n++)
		ImGui::Selectable("%04d: Some text", n);
	ImGui::EndChild();
	
	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}

void progTerminate()
{
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
}

int main(void)
{
	Window::CreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "React 3D", &refresh,
		&load, &progTerminate, &window);

	return 0;
}