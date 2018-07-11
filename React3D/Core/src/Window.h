#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

class Window
{
public:
	static void CreateWindow( int width, int height, 
		const char *title, void(*refresh)(), void(*load)() );
};