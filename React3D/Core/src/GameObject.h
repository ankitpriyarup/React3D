#pragma once
#include <iostream>
#include <unordered_map>
#include "component/Component.h"
#include "component/LightSource.h"
#include "component/MeshRenderer.h"
#include "component/Transform.h"

class GameObject
{
private:
	std::unordered_map<std::string, component::Component*> components;

public:
	GameObject(glm::mat4* _projectionMatrix, glm::mat4* _viewMatrix, glm::vec3 _position);
	GameObject(glm::mat4* _projectionMatrix, glm::mat4* _viewMatrix, glm::vec3 _position, glm::vec4 _rotation);
	GameObject(glm::mat4* _projectionMatrix, glm::mat4* _viewMatrix,
		glm::vec3 _position, glm::vec4 _rotation, glm::vec3 _scale);
	~GameObject();
	component::Component* GetComponent(std::string _componentName);
	void AddMeshRenderer(component::MeshRenderer* _meshRenderer);
	void AddLightSource(component::LightSource* _lightSource);
	void Render(Renderer* _renderer) const;
	void Update() const;
};