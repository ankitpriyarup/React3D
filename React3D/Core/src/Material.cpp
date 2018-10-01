#include "Material.h"

Material::Material(std::string _srcShader) : srcShader(_srcShader)
{
	std::ifstream stream(srcShader);
	if (!stream)
		throw std::invalid_argument("Could not open file " + srcShader);
	else
	{
		std::string line;
		bool flag = false;
		while (getline(stream, line))
		{
			if (!flag)
			{
				if (line.find("#shader fragment") != std::string::npos) flag = true;
				else continue;
			}
			if (line.find("uniform") != std::string::npos)
			{
				line = line.substr(0, line.length() - 1);

				std::regex rgx("\\s+");
				std::sregex_token_iterator iter(line.begin(), line.end(), rgx, -1);

				std::advance(iter, 1);
				Uniform* uniform;
				if (*iter == "sampler2D")
					uniform = new Uniform{ Uniform::Type::TEXTURE2D, new int };
				else if (*iter == "int")
					uniform = new Uniform{ Uniform::Type::INT, new int{0} };
				else if (*iter == "float")
					uniform = new Uniform{ Uniform::Type::FLOAT, new float{0.0f} };
				else if (*iter == "vec2")
					uniform = new Uniform{ Uniform::Type::VECTOR2, new float[2]{0.0f, 0.0f} };
				else if (*iter == "vec3")
					uniform = new Uniform{ Uniform::Type::VECTOR3, new float[3]{0.0f, 0.0f, 0.0f} };
				else if (*iter == "vec4")
					uniform = new Uniform{ Uniform::Type::VECTOR4, new float[4]{0.0f, 0.0f, 0.0f, 0.0f} };
				else break;

				std::advance(iter, 1);
				defaultUniforms.emplace(std::make_pair(*iter, uniform));
			}
		}
	}
}

Material::Material(std::string _srcShader, std::string _srcTex) : srcShader(_srcShader)
{
	std::ifstream stream(srcShader);
	if (!stream)
		throw std::invalid_argument("Could not open file " + srcShader);
	else
	{
		std::string line;
		bool flag = false;
		while (getline(stream, line))
		{
			if (!flag)
			{
				if (line.find("#shader fragment") != std::string::npos) flag = true;
				else continue;
			}
			if (line.find("uniform") != std::string::npos)
			{
				line = line.substr(0, line.length() - 1);

				std::regex rgx("\\s+");
				std::sregex_token_iterator iter(line.begin(), line.end(), rgx, -1);

				std::advance(iter, 1);
				Uniform* uniform;
				if (*iter == "sampler2D")
					uniform = new Uniform{ Uniform::Type::TEXTURE2D, new int };
				else if (*iter == "int")
					uniform = new Uniform{ Uniform::Type::INT, new int{ 0 } };
				else if (*iter == "float")
					uniform = new Uniform{ Uniform::Type::FLOAT, new float{ 0.0f } };
				else if (*iter == "vec2")
					uniform = new Uniform{ Uniform::Type::VECTOR2, new float[2]{ 0.0f, 0.0f } };
				else if (*iter == "vec3")
					uniform = new Uniform{ Uniform::Type::VECTOR3, new float[3]{ 0.0f, 0.0f, 0.0f } };
				else if (*iter == "vec4")
					uniform = new Uniform{ Uniform::Type::VECTOR4, new float[4]{ 0.0f, 0.0f, 0.0f, 0.0f } };
				else break;

				std::advance(iter, 1);
				defaultUniforms.emplace(std::make_pair(*iter, uniform));
			}
		}
	}
	textures.emplace_back(new Texture(_srcTex));
}

void Material::assignAlbedo(std::string _srcTex)
{
	if (textures.size() < 1)
		textures.emplace_back(new Texture(_srcTex));
	else
	{
		Texture* temp = textures[0];
		textures[0] = new Texture(_srcTex);
		delete temp;
	}
}

void Material::assignNormalMap(std::string _srcTex)
{
	if (textures.size() < 2)
		textures.emplace_back(new Texture(_srcTex));
	else
	{
		Texture* temp = textures[1];
		textures[1] = new Texture(_srcTex);
		delete temp;
	}
}

Material::~Material()
{
	while (!textures.empty())
	{
		Texture* temp = textures.back();
		textures.pop_back();
		delete temp;
	}
	for (auto it = defaultUniforms.begin(); it != defaultUniforms.end(); it++)
		delete it->second;
}

std::string Material::getShader() const
{
	return srcShader;
}