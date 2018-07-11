#include "EngineResources.h"
#include "Window.h"
#include "scene/Scene.h"
#include "scene/TestClearColor.h"
#include "Renderer.h"

scene::TestClearColor* test;
Renderer* renderer;

void load()
{
	test = new scene::TestClearColor;
	renderer = new Renderer;
}

void refresh()
{
	test->OnUpdate(0.0f);
	test->OnRender();
	ImGui_ImplGlfwGL3_NewFrame();
	test->OnGUI();
}

int main(void)
{
	Window::CreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "React 3D", &refresh, &load);

	return 0;
}