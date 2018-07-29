#include "Material.h"

Material::Material(std::string _srcShader)
{
	shader = new Shader(_srcShader);
	shader->Bind();
}

Material::Material(std::string _srcShader, std::string _srcTex)
{
	shader = new Shader(_srcShader);
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
	delete shader;	
}

Shader* Material::getShader() const
{
	return shader;
}

void Material::bind()
{
	shader->Bind();
	textures[0]->Bind(0);
	shader->SetUniform1i("albedo", 0);
}
