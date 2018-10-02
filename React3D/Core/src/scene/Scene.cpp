#include "Scene.h"

scene::Scene::Scene(Projection _projection, int* _width, int* _height) :
	width(_width), height(_height), projection(_projection)
{
	lastX = (GLfloat) (*width) / 2;
	lastY = (GLfloat) (*height) / 2;
	sceneCamera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	viewMatrix = new glm::mat4();
	*viewMatrix = sceneCamera->GetViewMatrix();

	switch (projection)
	{
	case Projection::Perspective:
		projectionMatrix = new glm::mat4(glm::perspective(45.0f, (GLfloat)*_width / (GLfloat)*_height, 0.1f, 1000.0f));
		break;
	case Projection::Orthographic:
		projectionMatrix = new glm::mat4(glm::ortho(0.0f, (GLfloat)*_width, 0.0f, (GLfloat)*_height, 0.1f, 1000.0f));
		break;
	}
}

scene::Scene::~Scene()
{
	for (auto it = gameObjects.begin(); it != gameObjects.end(); it++)
		delete it->second;

	delete projectionMatrix;
}

void scene::Scene::OnUpdate(double deltaTime)
{
	if (keys[KEY_W] || keys[KEY_UP])
	{
		sceneCamera->ProcessKeyboard(FORWARD, deltaTime);
		UpdateProjections();
	}

	if (keys[KEY_S] || keys[KEY_DOWN])
	{
		sceneCamera->ProcessKeyboard(BACKWARD, deltaTime);
		UpdateProjections();
	}

	if (keys[KEY_A] || keys[KEY_LEFT])
	{
		sceneCamera->ProcessKeyboard(LEFT, deltaTime);
		UpdateProjections();
	}

	if (keys[KEY_D] || keys[KEY_RIGHT])
	{
		sceneCamera->ProcessKeyboard(RIGHT, deltaTime);
		UpdateProjections();
	}
}

void scene::Scene::OnRender(Renderer * _renderer)
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glm::vec3 camView = getSceneCameraPosition();
	glm::vec3 camFront = getSceneCameraFront();
	
	for (auto it = gameObjects.begin(); it != gameObjects.end(); it++)
	{
		it->second->Render(_renderer);
		component::MeshRenderer* rend =
			(component::MeshRenderer*) it->second->GetComponent(component::MESH_RENDERER);
		if (rend != nullptr)
		{
			if (!rend->getMaterial()->containsViewUniform) continue;
			rend->getShader()->Bind();
			rend->getShader()->SetUniform3f("x_viewPos", camView.x, camView.y, camView.z);
			if (showSpotLight)
			{
				rend->getShader()->SetUniform3f("x_spotLight.position", camView.x, camView.y, camView.z);
				rend->getShader()->SetUniform3f("x_spotLight.direction", camFront.x, camFront.y, camFront.z);
			}
		}
	}
}

void scene::Scene::KeyCallback(int key, int scancode, int action, int mode)
{
	if (action == KEY_PRESS)
		keys[key] = true;
	else if (action == KEY_RELEASE)
		keys[key] = false;
}

void scene::Scene::MouseButtonCallback(int button, int action, int mode)
{
	if (action == KEY_PRESS)
	{
		firstMouse = true;
		mouseButtons[button] = true;
	}
	else if (action == KEY_RELEASE)
		mouseButtons[button] = false;
}

void scene::Scene::MouseCallback(double xPos, double yPos)
{
	if (!mouseButtons[KEY_MOUSE_BUTTON_RIGHT] && !mouseButtons[KEY_MOUSE_BUTTON_MIDDLE])
		return;

	if (firstMouse)
	{
		lastX = (GLfloat)xPos;
		lastY = (GLfloat)yPos;
		firstMouse = false;
	}

	GLfloat xOffset = (GLfloat)(xPos - lastX);
	GLfloat yOffset = (GLfloat)(lastY - yPos);

	if (mouseButtons[KEY_MOUSE_BUTTON_RIGHT])
		sceneCamera->ProcessMouseMovement(xOffset, yOffset);
	if (mouseButtons[KEY_MOUSE_BUTTON_MIDDLE])
		sceneCamera->ProcessPanMovement(xOffset, yOffset);

	UpdateProjections();
}

glm::vec3 scene::Scene::getSceneCameraPosition() const
{
	return sceneCamera->getPosition();
}

glm::vec3 scene::Scene::getSceneCameraFront() const
{
	return sceneCamera->getFront();
}

GameObject * scene::Scene::AddGameObject(std::string _name, glm::vec3 _position)
{
	if (gameObjects.find(_name) != gameObjects.end())
	{
		std::cout << "Error: Every gameobject should have a unique name." << std::endl;
		return nullptr;
	}
	GameObject* gb = new GameObject(projectionMatrix, viewMatrix, _position);
	gameObjects.insert(std::make_pair(_name, gb));
	return gb;
}

GameObject * scene::Scene::AddGameObject(std::string _name, glm::vec3 _position, glm::vec4 _rotation)
{
	if (gameObjects.find(_name) != gameObjects.end())
	{
		std::cout << "Error: Every gameobject should have a unique name." << std::endl;
		return nullptr;
	}
	GameObject* gb = new GameObject(projectionMatrix, viewMatrix, _position, _rotation);
	gameObjects.insert(std::make_pair(_name, gb));
	return gb;
}

GameObject * scene::Scene::AddGameObject(std::string _name, glm::vec3 _position, glm::vec4 _rotation, glm::vec3 _scale)
{
	if (gameObjects.find(_name) != gameObjects.end())
	{
		std::cout << "Error: Every gameobject should have a unique name." << std::endl;
		return nullptr;
	}
	GameObject* gb = new GameObject(projectionMatrix, viewMatrix, _position, _rotation, _scale);
	gameObjects.insert(std::make_pair(_name, gb));
	return gb;
}

void scene::Scene::UpdateProjections()
{
	*viewMatrix = sceneCamera->GetViewMatrix();

	for (auto it = gameObjects.begin(); it != gameObjects.end(); it++)
		it->second->GetComponent(component::TRANSFORM)->Update();
}

void scene::Scene::UpdateDirectionalLight(glm::vec3 _dirLightColor, glm::vec3 _dirLightDirection,
	glm::vec3 _dirLightAmbient, glm::vec3 _dirLightDiffuse, glm::vec3 _dirLightSpecular)
{
	dirLightColor = _dirLightColor;
	dirLightDirection = _dirLightDirection;
	dirLightAmbient = _dirLightAmbient;
	dirLightDiffuse = _dirLightDiffuse;
	dirLightSpecular = _dirLightSpecular;

	for (auto it = gameObjects.begin(); it != gameObjects.end(); it++)
	{
		component::MeshRenderer* rend =
			(component::MeshRenderer*) it->second->GetComponent(component::MESH_RENDERER);
		if (rend != nullptr)
		{
			if (!rend->getMaterial()->containsViewUniform) continue;
			rend->getShader()->Bind();
			rend->getShader()->SetUniform3f("x_dirLight.color", dirLightColor.x, dirLightColor.y, dirLightColor.z);
			rend->getShader()->SetUniform3f("x_dirLight.direction", dirLightDirection.x, dirLightDirection.y, dirLightDirection.z);
			rend->getShader()->SetUniform3f("x_dirLight.ambient", dirLightAmbient.x, dirLightAmbient.y, dirLightAmbient.z);
			rend->getShader()->SetUniform3f("x_dirLight.diffuse", dirLightDiffuse.x, dirLightDiffuse.y, dirLightDiffuse.z);
			rend->getShader()->SetUniform3f("x_dirLight.specular", dirLightSpecular.x, dirLightSpecular.y, dirLightSpecular.z);
		}
	}
}

void scene::Scene::SetSpotLight(glm::vec3 _spotLightColor, glm::vec3 _spotLightAmbient,
	glm::vec3 _spotLightDiffuse, glm::vec3 _spotLightSpecular, float _spotLightConstant, float _spotLightLinear,
	float _spotLightQuadratic, float _spotLightCutOffAngle, float _spotLightOuterCutOffAngle)
{
	showSpotLight = true;
	spotLightColor = _spotLightColor;
	spotLightAmbient = _spotLightAmbient;
	spotLightDiffuse = _spotLightDiffuse;
	spotLightSpecular = _spotLightSpecular;
	spotLightConstant = _spotLightConstant;
	spotLightLinear = _spotLightLinear;
	spotLightQuadratic = _spotLightQuadratic;
	spotLightCutOffAngle = _spotLightCutOffAngle;
	spotLightOuterCutOffAngle = _spotLightOuterCutOffAngle;

	for (auto it = gameObjects.begin(); it != gameObjects.end(); it++)
	{
		component::MeshRenderer* rend =
			(component::MeshRenderer*) it->second->GetComponent(component::MESH_RENDERER);
		if (rend != nullptr)
		{
			if (!rend->getMaterial()->containsViewUniform) continue;
			rend->getShader()->Bind();
			rend->getShader()->SetUniform3f("x_spotLight.color", spotLightColor.x, spotLightColor.y, spotLightColor.z);
			rend->getShader()->SetUniform3f("x_spotLight.ambient", spotLightAmbient.x, spotLightAmbient.y, spotLightAmbient.z);
			rend->getShader()->SetUniform3f("x_spotLight.diffuse", spotLightDiffuse.x, spotLightDiffuse.y, spotLightDiffuse.z);
			rend->getShader()->SetUniform3f("x_spotLight.specular", spotLightSpecular.x, spotLightSpecular.y, spotLightSpecular.z);
			rend->getShader()->SetUniform1f("x_spotLight.constant", spotLightConstant);
			rend->getShader()->SetUniform1f("x_spotLight.linear", spotLightLinear);
			rend->getShader()->SetUniform1f("x_spotLight.quadratic", spotLightQuadratic);
			rend->getShader()->SetUniform1f("x_spotLight.cutOff", glm::cos(glm::radians(spotLightCutOffAngle)));
			rend->getShader()->SetUniform1f("x_spotLight.outerCutOff", glm::cos(glm::radians(spotLightOuterCutOffAngle)));
		}
	}
}

void scene::Scene::performLightningCalculations()
{
	for (auto it = gameObjects.begin(); it != gameObjects.end(); it++)
	{
		component::MeshRenderer* rend =
			(component::MeshRenderer*) it->second->GetComponent(component::MESH_RENDERER);
		if (rend != nullptr)
		{
			rend->getShader()->Bind();
			int counter = 0;
			for (auto tmp = gameObjects.begin(); tmp != gameObjects.end(); tmp++)
			{
				component::LightSource* lightSrc =
					(component::LightSource*) tmp->second->GetComponent(component::LIGHT_SOURCE);
				if (lightSrc != nullptr)
				{
					component::Transform* transform =
						(component::Transform*) tmp->second->GetComponent(component::TRANSFORM);

					rend->getShader()->SetUniform1i("x_pointLightsCount", pointLightCount);
					rend->getShader()->SetUniform3f("x_pointLights[" + std::to_string(counter) + "].color",
						lightSrc->getColor().x, lightSrc->getColor().y, lightSrc->getColor().z);
					rend->getShader()->SetUniform3f("x_pointLights[" + std::to_string(counter) + "].position",
						transform->getPosition().x, transform->getPosition().y, transform->getPosition().z);
					rend->getShader()->SetUniform3f("x_pointLights[" + std::to_string(counter) + "].ambient",
						lightSrc->getAmbient().x, lightSrc->getAmbient().y, lightSrc->getAmbient().z);
					rend->getShader()->SetUniform3f("x_pointLights[" + std::to_string(counter) + "].diffuse",
						lightSrc->getDiffuse().x, lightSrc->getDiffuse().y, lightSrc->getDiffuse().z);
					rend->getShader()->SetUniform3f("x_pointLights[" + std::to_string(counter) + "].specular",
						lightSrc->getSpecular().x, lightSrc->getSpecular().y, lightSrc->getSpecular().z);
					rend->getShader()->SetUniform1f("x_pointLights[" + std::to_string(counter) + "].constant", lightSrc->getConstant());
					rend->getShader()->SetUniform1f("x_pointLights[" + std::to_string(counter) + "].linear", lightSrc->getLinear());
					rend->getShader()->SetUniform1f("x_pointLights[" + std::to_string(counter) + "].quadratic", lightSrc->getQuadratic());
					++counter;
				}
			}
		}
	}
}
