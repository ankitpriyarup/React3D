#include "GameObject.h"

GameObject::GameObject(glm::mat4* _projectionMatrix, glm::mat4* _viewMatrix, glm::vec3 _position)
{
	component::Transform* transform = new component::Transform(_projectionMatrix, _viewMatrix,
		_position, component::rotZero, component::vecOne);
	components.insert(std::make_pair(transform->GetComponentName(), transform));

	transform->gameObject = this;
}

GameObject::~GameObject()
{
	for (auto it = components.begin(); it != components.end(); it++)
		delete it->second;
}

component::Component* GameObject::GetComponent(std::string _componentName)
{
	if (components.find(_componentName) != components.end())
		return components[_componentName];
	else
		return nullptr;
}

void GameObject::AddMeshRenderer(component::MeshRenderer * _meshRenderer)
{
	auto it = components.find(component::MESH_RENDERER);
	if (it == components.end())
	{
		_meshRenderer->gameObject = this;
		components.insert(std::make_pair(_meshRenderer->GetComponentName(), _meshRenderer));
		GetComponent(component::TRANSFORM)->Update();
	}
}

void GameObject::Render(Renderer* _renderer) const
{
	auto it = components.begin();
	for (auto it = components.begin(); it != components.end(); it++)
		it->second->Render(_renderer);
}

void GameObject::Update() const
{
	auto it = components.begin();
	for (auto it = components.begin(); it != components.end(); it++)
		it->second->Update();
}
