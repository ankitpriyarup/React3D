#pragma once
#include "Scene.h"

namespace scene
{
	class TestClearColor : public Scene
	{
	private:
		Material* texMat;

	public:
		std::vector<GameObject*> gameObjects;

		TestClearColor(glm::mat4& _projectionMatrix);
		~TestClearColor();
		void OnUpdate(float deltaTime) override;
		void OnRender(Renderer* _renderer) override;

	private:
		glm::mat4 projectionMatrix;
	};
}
