#include "TestClearColor.h"
#include "Renderer.h"

namespace scene
{
	scene::TestClearColor::TestClearColor()
		: clearColors{ 0.2f, 0.3f, 0.8f, 1.0f }
	{
	}

	scene::TestClearColor::~TestClearColor()
	{
	}

	void TestClearColor::OnUpdate(float deltaTime)
	{
	}

	void TestClearColor::OnRender()
	{
		GLCall(glClearColor(clearColors[0], clearColors[1], clearColors[2], clearColors[4]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}
}