#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "stb_image/stb_image.h"

class Window
{
public:
	static void CreateWindow( int width, int height, const char* iconPath,
		const char* title, void(*refresh)(), void(*load)() ,
		void(*terminate)(), GLFWwindow** window);
};