#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Window
{
public:
	static void CreateWindow( int width, int height, 
		const char *title, void(*update)(), void(*start)() );
};