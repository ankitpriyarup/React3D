#pragma once
#include <unordered_map>
#include "Renderer.h"
#include "GameObject.h"
#include "component/Component.h"
#include "component/Transform.h"
#include "component/MeshRenderer.h"

namespace scene
{
	class Scene
	{
	public:
		enum Projection { Perspective, Orthographic };

		int* width;
		int* height;
		Projection projection;
		glm::mat4* projectionMatrix;
		std::unordered_map<std::string, GameObject*> gameObjects;

		Scene(Projection _projection, int* _width, int* _height);
		virtual ~Scene();
		virtual void OnUpdate(float deltaTime) { };
		virtual void OnRender(Renderer* _renderer);
		GameObject* AddGameObject(std::string _name, glm::vec3 _position);
	};
}