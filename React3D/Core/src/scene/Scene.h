#pragma once
#include <unordered_map>
#include "Input.h"
#include "Renderer.h"
#include "Camera.h"
#include "GameObject.h"
#include "component/Component.h"
#include "component/Transform.h"
#include "component/MeshRenderer.h"

namespace scene
{
	class Scene
	{
	private:
		bool keys[1024];
		bool mouseButtons[3];
		Camera* sceneCamera;
		float lastX;
		float lastY;
		bool firstMouse = true;

	public:
		enum Projection { Perspective, Orthographic };

		int* width;
		int* height;
		Projection projection;
		glm::mat4* projectionMatrix;
		glm::mat4* viewMatrix;
		std::unordered_map<std::string, GameObject*> gameObjects;

		Scene(Projection _projection, int* _width, int* _height);
		virtual ~Scene();
		virtual void OnUpdate(double deltaTime);
		virtual void OnRender(Renderer* _renderer);
		void KeyCallback(int key, int scancode, int action, int mode);
		void MouseButtonCallback(int button, int action, int mode);
		void MouseCallback(double xPos, double yPos);
		GameObject* AddGameObject(std::string _name, glm::vec3 _position);
		void UpdateProjections();
	};
}