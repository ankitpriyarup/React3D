#include "Material.h"

Material::Material(std::string _srcShader) : srcShader(_srcShader)
{
}

Material::Material(std::string _srcShader, std::string _srcTex) : srcShader(_srcShader)
{
	textures.emplace_back(new Texture(_srcTex));
}

Material::~Material()
{
	while (!textures.empty())
	{
		Texture* temp = textures.back();
		textures.pop_back();
		delete temp;
	}
}

std::string Material::getShader() const
{
	return srcShader;
}