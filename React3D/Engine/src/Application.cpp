#include "EngineResources.h"
#include "EngineUI.h"
#include "Window.h"
#include "scene/Scene.h"
#include "Renderer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "scene/TestObjectRendering.h"

scene::TestObjectRendering* activeScene;
Renderer* renderer;
glm::mat4 screenProjection;
GLFWwindow* window;
int width = SCREEN_WIDTH;
int height = SCREEN_HEIGHT;

void load()
{
	renderer = new Renderer;

	activeScene = new scene::TestObjectRendering(&width, &height);
	EngineUI::CreateUIContext(window);
}

void refresh()
{
	glfwGetWindowSize(window, &width, &height);
	activeScene->OnRender(renderer);
	activeScene->OnUpdate(0);
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
	Window::CreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, Window::MAXIMIZED, "res/textures/icon_react_small.png",
		"React 3D", &refresh, &load, &progTerminate, &window);

	return 0;
}