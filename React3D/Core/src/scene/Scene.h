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
		Camera* sceneCamera;
		GLfloat lastX;
		GLfloat lastY;
		bool firstMouse = true;
		bool buttonRightPressed = false;

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
		virtual void OnUpdate(float deltaTime);
		virtual void OnRender(Renderer* _renderer);
		void KeyCallback(int key, int scancode, int action, int mode);
		void MouseButtonCallback(int button, int action, int mode);
		void MouseCallback(double xPos, double yPos);
		void ScrollCallback(double xOffset, double yOffset);
		GameObject* AddGameObject(std::string _name, glm::vec3 _position);
	};
}