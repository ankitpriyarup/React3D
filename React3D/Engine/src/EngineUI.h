#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"
#include "Window.h"

class EngineUI
{
private:
	static ImFont* defaultFont;
	static ImFont* curFont;

public:
	static void DrawDefaultScreen();
	static void CreateUIContext(GLFWwindow* window);
	static void TerminateUIContext();
};