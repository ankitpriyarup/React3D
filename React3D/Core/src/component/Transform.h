#pragma once
#include "Component.h"
#include "GameObject.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace component
{
	const static std::string TRANSFORM = "Transform";
	const static glm::vec3 vecZero = glm::vec3(0, 0, 0);
	const static glm::vec3 vecOne = glm::vec3(1, 1, 1);

	class Transform : public Component
	{
	private:
		int* projectionWidth;
		int* projectionHeight;
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;

	public:
		Transform(int* _projectionWidth, int* _projectionHeight,
			glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale);
		~Transform();
		void Load();
		void Render(Renderer* _renderer) override;
		void setPosition(glm::vec3 _position);
		glm::vec3 getPosition();
		void setRotation(glm::vec3 _rotation);
		glm::vec3 getRotation();
		void setScale(glm::vec3 _scale);
		glm::vec3 getScale();
		void Reset() override;
		std::string GetComponentName() override;
	};
}