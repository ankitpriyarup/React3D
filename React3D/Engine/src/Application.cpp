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
double deltaTime = 0.0f;
double lastFrame = 0.0f;

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
	glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mode)
	{
		if (activeScene == nullptr)
			return;
		if (key >= 0 && key < 1024)
			activeScene->KeyCallback(key, scancode, action, mode);
	});
	glfwSetCursorPosCallback(window, [](GLFWwindow *window, double xPos, double yPos)
	{
		if (activeScene == nullptr)
			return;
		activeScene->MouseCallback(xPos, yPos);
	});
	glfwSetMouseButtonCallback(window, [](GLFWwindow *window, int button, int action, int mode)
	{
		if (activeScene == nullptr)
			return;
		activeScene->MouseButtonCallback(button, action, mode);
	});

	glfwGetWindowSize(window, &width, &height);

	double currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	if (activeScene != nullptr)
	{
		activeScene->OnRender(renderer);
		activeScene->OnUpdate(deltaTime);
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