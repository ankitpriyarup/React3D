#pragma once
#include "Scene.h"

namespace scene
{
	class TestObjectRendering : public Scene
	{
	private:
		Material* texMat;

	public:
		glm::mat4& projectionMatrix;
		std::vector<GameObject*> gameObjects;

		TestObjectRendering(glm::mat4& _projectionMatrix);
		~TestObjectRendering();
		void OnUpdate(float deltaTime) override;
		void OnRender(Renderer* _renderer) override;
	};
}
