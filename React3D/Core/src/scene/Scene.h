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
		glm::vec3 dirLightColor;
		glm::vec3 dirLightDirection;
		glm::vec3 dirLightAmbient;
		glm::vec3 dirLightDiffuse;
		glm::vec3 dirLightSpecular;
		glm::vec3 spotLightColor;
		glm::vec3 spotLightAmbient;
		glm::vec3 spotLightDiffuse;
		glm::vec3 spotLightSpecular;
		float spotLightConstant;
		float spotLightLinear;
		float spotLightQuadratic;
		float spotLightCutOffAngle;
		float spotLightOuterCutOffAngle;
		bool showSpotLight = false;

	public:
		enum Projection { Perspective, Orthographic };

		int* width;
		int* height;
		int pointLightCount = 0;
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
		glm::vec3 getSceneCameraPosition() const;
		glm::vec3 getSceneCameraFront() const;
		GameObject* AddGameObject(std::string _name, glm::vec3 _position);
		GameObject* AddGameObject(std::string _name, glm::vec3 _position, glm::vec4 _rotation);
		GameObject* AddGameObject(std::string _name,
			glm::vec3 _position, glm::vec4 _rotation, glm::vec3 _scale);
		void UpdateProjections();
		void UpdateDirectionalLight(glm::vec3 _dirLightColor, glm::vec3 _dirLightDirection,
			glm::vec3 _dirLightAmbient, glm::vec3 _dirLightDiffuse, glm::vec3 _dirLightSpecular);
		void SetSpotLight(glm::vec3 _spotLightColor, glm::vec3 _spotLightAmbient,
			glm::vec3 _spotLightDiffuse, glm::vec3 _spotLightSpecular, float _constant, float _linear,
			float _quadratic, float _cutOffAngle, float _outerCutOffAngle);
		void performLightningCalculations();
	};
}