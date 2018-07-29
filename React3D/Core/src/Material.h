#pragma once
#include "Shader.h"
#include "Texture.h"

class Material
{
private:
	std::vector<Texture*> textures;
	Shader* shader;

public:
	Material(std::string _srcShader);
	Material(std::string _srcShader, std::string _srcTex);
	~Material();
	Shader* getShader() const;
	void bind();
};