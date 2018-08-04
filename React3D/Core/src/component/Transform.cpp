#include "Transform.h"

component::Transform::Transform(glm::mat4* _projectionMatrix, glm::mat4* _viewMatrix,
	glm::vec3 _position, glm::vec4 _rotation, glm::vec3 _scale)
	: projectionMatrix(_projectionMatrix), viewMatrix(_viewMatrix),
	position(_position), rotation(_rotation), scale(_scale)
{
}

component::Transform::~Transform()
{
}

void component::Transform::Update()
{
	MeshRenderer* meshRenderer = (MeshRenderer*)gameObject->GetComponent(MESH_RENDERER);
	if (meshRenderer == nullptr)
		return;

	glm::mat4 modelMatrix;
	modelMatrix = glm::translate(glm::mat4(1.0f), position);
	modelMatrix = glm::rotate(modelMatrix, rotation.w, glm::vec3(rotation.x, rotation.y, rotation.z));
	modelMatrix = glm::scale(modelMatrix, scale);
	meshRenderer->getShader()->Bind();
	meshRenderer->getShader()->SetUniformMat4f("u_MVP", (*projectionMatrix) * (*viewMatrix) * modelMatrix);
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
