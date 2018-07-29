#include "Transform.h"

component::Transform::Transform(glm::mat4& _projectionMatrix,
	glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale)
	: projectionMatrix(_projectionMatrix), position(_position), rotation(_rotation), scale(_scale)
{
}

component::Transform::~Transform()
{
}

void component::Transform::Load()
{
	MeshRenderer* meshRenderer = (MeshRenderer*) gameObject->GetComponent(MESH_RENDERER);
	meshRenderer->getMaterial()->getShader()->SetUniformMat4f("u_MVP", 
		projectionMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)));
}

void component::Transform::Render(Renderer* _renderer)
{
}

void component::Transform::setPosition(glm::vec3 _position)
{
	position = _position;
	Load();
}

glm::vec3 component::Transform::getPosition()
{
	return position;
}

void component::Transform::setRotation(glm::vec3 _rotation)
{
	rotation = _rotation;
}

glm::vec3 component::Transform::getRotation()
{
	return rotation;
}

void component::Transform::setScale(glm::vec3 _scale)
{
	scale = _scale;
}

glm::vec3 component::Transform::getScale()
{
	return scale;
}

void component::Transform::Reset()
{
}

std::string component::Transform::GetComponentName()
{
	return component::TRANSFORM;
}
