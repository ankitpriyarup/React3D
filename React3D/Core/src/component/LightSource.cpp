#include "LightSource.h"

component::LightSource::LightSource(glm::vec3 _color, glm::vec3 _ambient,
	glm::vec3 _diffuse, glm::vec3 _specular, float _constant,
	float _linear, float _quadratic) :
	color(_color), ambient(_ambient), diffuse(_diffuse), specular(_specular),
	constant(_constant), linear(_linear), quadratic(_quadratic)
{ }

component::LightSource::~LightSource()
{
}

glm::vec3 component::LightSource::getColor()
{
	return color;
}

glm::vec3 component::LightSource::getAmbient()
{
	return ambient;
}

glm::vec3 component::LightSource::getDiffuse()
{
	return diffuse;
}

glm::vec3 component::LightSource::getSpecular()
{
	return specular;
}

float component::LightSource::getConstant()
{
	return constant;
}

float component::LightSource::getLinear()
{
	return linear;
}

float component::LightSource::getQuadratic()
{
	return 0.0f;
}

void component::LightSource::Update()
{
}

void component::LightSource::Render(Renderer * _renderer)
{
}

std::string component::LightSource::GetComponentName()
{
	return component::LIGHT_SOURCE;
}

void component::LightSource::Reset()
{
}
