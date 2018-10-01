#pragma once
#include <iostream>
#include <fstream>
#include <regex>
#include <iterator>
#include <string.h>
#include <map>
#include "Texture.h"
#include "Uniform.h"

class Material
{
private:
	std::string srcShader;

public:
	std::vector<Texture*> textures;
	std::unordered_map<std::string, Uniform*> defaultUniforms;

	Material(std::string _srcShader);
	Material(std::string _srcShader, std::string _srcTex);
	void assignAlbedo(std::string _srcTex);
	void assignNormalMap(std::string _srcTex);
	~Material();
	std::string getShader() const;
};