#include "Window.h"

void Window::CreateWindow(int& width, int& height, WindowState state, const char* iconPath,
	const char* title, void(*refresh)(), void(*load)(),
	void(*terminate)(), GLFWwindow** window)
{
	if (!glfwInit())
		return;

	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	switch (state)
	{
		case Window::RESTORED_DOWN:
		{
			(*window) = glfwCreateWindow(width, height, title, NULL, NULL);
			break;
		}
		case Window::MAXIMIZED:
		{
			(*window) = glfwCreateWindow(mode->width, mode->height, title, NULL, NULL);
			width = mode->width;
			height = mode->height;
			glfwMaximizeWindow(*window);
			break;
		}
		case Window::FULLSCREEN:
		{
			(*window) = glfwCreateWindow(mode->width, mode->height, title, glfwGetPrimaryMonitor(), NULL);
			break;
		}
	}

	if (!window)
	{
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(*window);
	glfwSwapInterval(1);

	GLFWimage icons[1];
	icons[0].pixels = stbi_load(iconPath, &icons[0].width, &icons[0].height, 0, 4);
	glfwSetWindowIcon(*window, 1, icons);
	stbi_image_free(icons[0].pixels);

	if (glewInit() != GLEW_OK)
		std::cout << "Error!" << std::endl;

	std::cout << "[DEBUG BUILD] OpenGL Version: " <<
		glGetString(GL_VERSION) << " " <<
		glGetString(GL_RENDERER) <<
		std::endl;

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	load();

	while (!glfwWindowShouldClose(*window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		refresh();

		glfwSwapBuffers(*window);
		glfwPollEvents();
	}

	
	glfwTerminate();
}
