#pragma once
#include "Component.h"
#include "glm/glm.hpp"

namespace component
{
	static std::string LIGHT_SOURCE = "LightSource";

	class LightSource : public Component
	{
	private:
		glm::vec3 lightColor;

	public:
		LightSource(glm::vec3 _color);
		~LightSource();
		void setColor(glm::vec3 _color);
		glm::vec3 getColor();

		void Update() override;
		void Render(Renderer* _renderer) override;
		std::string GetComponentName() override;
		void Reset() override;
	};
}