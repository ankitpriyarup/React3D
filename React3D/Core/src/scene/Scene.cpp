#include "Scene.h"

scene::Scene::Scene(Projection _projection, int* _width, int* _height) :
	width(_width), height(_height), projection(_projection)
{
	switch (projection)
	{
	case Projection::Perspective:
	{
		projectionMatrix = new glm::mat4(glm::perspective(45.0f, (float)*_width / (float)*_height, 0.0f, 1000.0f));
		break;
	}
	case Projection::Orthographic:
	{
		projectionMatrix = new glm::mat4(glm::ortho(0.0f, (float)*_width, 0.0f, (float)*_height, 0.0f, 1000.0f));
		break;
	}
	default:
		break;
	}
}

scene::Scene::~Scene()
{
	for (auto it = gameObjects.begin(); it != gameObjects.end(); it++)
		delete it->second;

	delete projectionMatrix;
}

void scene::Scene::OnRender(Renderer * _renderer)
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	for (auto it = gameObjects.begin(); it != gameObjects.end(); it++)
		it->second->Render(_renderer);
}

GameObject * scene::Scene::AddGameObject(std::string _name, glm::vec3 _position)
{
	GameObject* gb = new GameObject(projectionMatrix, _position);
	gameObjects.insert(std::make_pair(_name, gb));
	return gb;
}
