#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "stb_image/stb_image.h"

class Window
{

public:
	enum WindowState { RESTORED_DOWN, MAXIMIZED, FULLSCREEN };

	static void CreateWindow(int& width, int& height, WindowState state, const char* iconPath,
		const char* title, void(*refresh)(), void(*load)() ,
		void(*terminate)(), GLFWwindow** window);
};