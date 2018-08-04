#pragma once
#include "Scene.h"

namespace scene
{
	class TestObjectRendering : public Scene
	{
	private:
		Material* texMat;

	public:
		TestObjectRendering(int* _width, int* _height);
		~TestObjectRendering();
		void OnUpdate(float deltaTime) override;
		void OnRender(Renderer* _renderer) override;
	};
}
