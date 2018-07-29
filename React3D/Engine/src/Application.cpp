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

void load()
{
	renderer = new Renderer;
	screenProjection = glm::ortho(0.0f, (float)SCREEN_WIDTH, 0.0f, (float)SCREEN_HEIGHT, -1.0f, 1.0f);

	activeScene = new scene::TestObjectRendering(screenProjection);
	EngineUI::CreateUIContext(window);
}

void refresh()
{
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
	Window::CreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT,"res/textures/icon_react_small.png",
		"React 3D", &refresh, &load, &progTerminate, &window);

	return 0;
}