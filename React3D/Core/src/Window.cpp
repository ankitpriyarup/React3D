#include "Window.h"

void Window::CreateWindow( int width, int height,
	const char * title, void (*update)(), void (*start)() )
{
	GLFWwindow* window;

	if (!glfwInit())
		return;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		std::cout << "Error!" << std::endl;

	std::cout << "[DEBUG BUILD] OpenGL Version: " <<
		glGetString(GL_VERSION) <<
		std::endl;

	start();

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		update();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}
