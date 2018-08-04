#include "EngineUI.h"
#include "Window.h"
#include "scene/Scene.h"
#include "Renderer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#if _DEBUG
#include "scene/TestObjectRendering.h"
#endif

scene::Scene* activeScene;
Renderer* renderer;
glm::mat4 screenProjection;
GLFWwindow* window;
int width, height;

void load()
{
	renderer = new Renderer;

#if _DEBUG
	activeScene = new scene::TestObjectRendering(&width, &height);
#endif
	EngineUI::CreateUIContext(window);
}

void refresh()
{
	glfwGetWindowSize(window, &width, &height);
	if (activeScene != nullptr)
	{
		activeScene->OnRender(renderer);
		activeScene->OnUpdate(0);
	}
	EngineUI::DrawDefaultScreen();
}

void progTerminate()
{
	EngineUI::TerminateUIContext();

	delete activeScene;
	delete renderer;
}

int main(void)
{
	Window::CreateWindow(width, height, Window::MAXIMIZED, "res/textures/icon_react_small.png",
		"React 3D", &refresh, &load, &progTerminate, &window);

	return 0;
}