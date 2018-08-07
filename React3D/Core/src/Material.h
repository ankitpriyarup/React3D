#pragma once
#include "Texture.h"

class Material
{
private:
	std::string srcShader;

public:
	std::vector<Texture*> textures;

	Material(std::string _srcShader);
	Material(std::string _srcShader, std::string _srcTex);
	~Material();
	std::string getShader() const;
};