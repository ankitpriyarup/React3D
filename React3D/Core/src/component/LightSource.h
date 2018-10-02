#pragma once
#include "Component.h"
#include "glm/glm.hpp"

namespace component
{
	static std::string LIGHT_SOURCE = "LightSource";

	class LightSource : public Component
	{
	private:
		glm::vec3 color;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float constant;
		float linear;
		float quadratic;

	public:
		LightSource(glm::vec3 _color, glm::vec3 _ambient, glm::vec3 _diffuse,
			glm::vec3 _specular, float _constant, float _linear, float _quadratic);
		~LightSource();
		glm::vec3 getColor();
		glm::vec3 getAmbient();
		glm::vec3 getDiffuse();
		glm::vec3 getSpecular();
		float getConstant();
		float getLinear();
		float getQuadratic();

		void Update() override;
		void Render(Renderer* _renderer) override;
		std::string GetComponentName() override;
		void Reset() override;
	};
}