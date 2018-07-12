#pragma once
#include "Scene.h"

namespace scene
{
	class TestClearColor : public Scene
	{
	public:
		TestClearColor();
		~TestClearColor();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;

	private:
		float clearColors[4];
	};
}
