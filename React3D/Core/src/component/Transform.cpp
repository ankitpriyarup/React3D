#include "Transform.h"

component::Transform::Transform(int* _projectionWidth, int* _projectionHeight,
	glm::vec3 _position, glm::vec4 _rotation, glm::vec3 _scale)
	: projectionWidth(_projectionWidth), projectionHeight(_projectionHeight), rotation(_rotation), scale(_scale)
{
}

component::Transform::~Transform()
{
}

void component::Transform::UpdateTransform()
{
	MeshRenderer* meshRenderer = (MeshRenderer*)gameObject->GetComponent(MESH_RENDERER);
	glm::mat4 projectionMatrix = glm::ortho(0.0f, (float)*projectionWidth, 0.0f, (float)*projectionHeight, -1.0f, 1.0f);
	glm::mat4 viewMatrix;
	viewMatrix = glm::translate(glm::mat4(1.0f), position);
	viewMatrix = glm::rotate(viewMatrix, rotation.w, glm::vec3(rotation.x, rotation.y, rotation.z));
	viewMatrix = glm::scale(viewMatrix, scale);
	meshRenderer->getMaterial()->getShader()->SetUniformMat4f("u_MVP", projectionMatrix * viewMatrix);
}

void component::Transform::Render(Renderer* _renderer)
{
}

void component::Transform::setPosition(glm::vec3 _position)
{
	position = _position;
}

glm::vec3 component::Transform::getPosition()
{
	return position;
}

void component::Transform::setRotation(glm::vec4 _rotation)
{
	rotation = _rotation;
}

glm::vec4 component::Transform::getRotation()
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
