#include "LightSource.h"

component::LightSource::LightSource(glm::vec3 _color)
{
	setColor(_color);
}

component::LightSource::~LightSource()
{
}

void component::LightSource::setColor(glm::vec3 _color)
{
	lightColor = _color;
}

glm::vec3 component::LightSource::getColor()
{
	return lightColor;
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
