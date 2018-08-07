#include "Scene.h"

scene::Scene::Scene(Projection _projection, int* _width, int* _height) :
	width(_width), height(_height), projection(_projection)
{
	lastX = (*width) / 2;
	lastY = (*height) / 2;
	sceneCamera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	viewMatrix = new glm::mat4();
	*viewMatrix = sceneCamera->GetViewMatrix();

	switch (projection)
	{
	case Projection::Perspective:
		projectionMatrix = new glm::mat4(glm::perspective(sceneCamera->GetZoom(), (float)*_width / (float)*_height, 0.0f, 1000.0f));
		break;
	case Projection::Orthographic:
		projectionMatrix = new glm::mat4(glm::ortho(0.0f, (float)*_width, 0.0f, (float)*_height, 0.0f, 1000.0f));
		break;
	}
}

scene::Scene::~Scene()
{
	for (auto it = gameObjects.begin(); it != gameObjects.end(); it++)
		delete it->second;

	delete projectionMatrix;
}

void scene::Scene::OnUpdate(float deltaTime)
{
	if (keys[KEY_W] || keys[KEY_UP])
		sceneCamera->ProcessKeyboard(FORWARD, deltaTime);

	if (keys[KEY_S] || keys[KEY_DOWN])
		sceneCamera->ProcessKeyboard(BACKWARD, deltaTime);

	if (keys[KEY_A] || keys[KEY_LEFT])
		sceneCamera->ProcessKeyboard(LEFT, deltaTime);

	if (keys[KEY_D] || keys[KEY_RIGHT])
		sceneCamera->ProcessKeyboard(RIGHT, deltaTime);
}

void scene::Scene::OnRender(Renderer * _renderer)
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	for (auto it = gameObjects.begin(); it != gameObjects.end(); it++)
		it->second->Render(_renderer);
}

void scene::Scene::KeyCallback(int key, int scancode, int action, int mode)
{
	if (action == KEY_PRESS)
		keys[key] = true;
	else if (action == KEY_RELEASE)
		keys[key] = false;
	*viewMatrix = sceneCamera->GetViewMatrix();
}

void scene::Scene::MouseButtonCallback(int button, int action, int mode)
{
	if (button == KEY_MOUSE_BUTTON_RIGHT)
	{
		if (action == KEY_PRESS)
			buttonRightPressed = true;
		else if (action == KEY_RELEASE)
			buttonRightPressed = false;
	}
}

void scene::Scene::MouseCallback(double xPos, double yPos)
{
	if (!buttonRightPressed)
		return;

	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;

	lastX = xPos;
	lastY = yPos;

	sceneCamera->ProcessMouseMovement(xOffset, yOffset);
	*viewMatrix = sceneCamera->GetViewMatrix();
	for (auto it = gameObjects.begin(); it != gameObjects.end(); it++)
		it->second->GetComponent(component::TRANSFORM)->Update();
}

void scene::Scene::ScrollCallback(double xOffset, double yOffset)
{
	sceneCamera->ProcessMouseScroll(yOffset);
	*viewMatrix = sceneCamera->GetViewMatrix();
}

GameObject * scene::Scene::AddGameObject(std::string _name, glm::vec3 _position)
{
	GameObject* gb = new GameObject(projectionMatrix, viewMatrix, _position);
	gameObjects.insert(std::make_pair(_name, gb));
	return gb;
}
