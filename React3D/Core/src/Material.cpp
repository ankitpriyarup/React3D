#include "Material.h"

Material::Material(std::string _srcShader) : srcShader(_srcShader)
{
	std::ifstream stream(srcShader);
	if (!stream)
		throw std::invalid_argument("Could not open file " + srcShader);
	else
	{
		std::string line;
		while (getline(stream, line))
		{
			if (line.find("uniform") != std::string::npos &&
				line.find("u_MVP") == std::string::npos)
			{
				line = line.substr(0, line.length() - 1);

				std::regex rgx("\\s+");
				std::sregex_token_iterator iter(line.begin(), line.end(), rgx, -1);

				std::advance(iter, 1);
				Uniform* uniform;
				if (*iter == "sampler2D")
					uniform = new Uniform{ Uniform::Type::TEXTURE2D, new int };
				else if (*iter == "int")
					uniform = new Uniform{ Uniform::Type::INT, new int };
				else if (*iter == "float")
					uniform = new Uniform{ Uniform::Type::FLOAT, new float };
				else if (*iter == "vec2")
					uniform = new Uniform{ Uniform::Type::VECTOR2, new float[2] };
				else if (*iter == "vec3")
					uniform = new Uniform{ Uniform::Type::VECTOR3, new float[3] };
				else if (*iter == "vec4")
					uniform = new Uniform{ Uniform::Type::VECTOR4, new float[4] };

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
		while (getline(stream, line))
		{
			if (line.find("uniform") != std::string::npos &&
				line.find("u_MVP") == std::string::npos)
			{
				line = line.substr(0, line.length() - 1);

				std::regex rgx("\\s+");
				std::sregex_token_iterator iter(line.begin(), line.end(), rgx, -1);

				std::advance(iter, 1);
				Uniform* uniform;
				if (*iter == "sampler2D")
					uniform = new Uniform{ Uniform::Type::TEXTURE2D, new int };
				else if (*iter == "int")
					uniform = new Uniform{ Uniform::Type::INT, new int(0) };
				else if (*iter == "float")
					uniform = new Uniform{ Uniform::Type::FLOAT, new float(1.0f) };
				else if (*iter == "vec2")
					uniform = new Uniform{ Uniform::Type::VECTOR2, new float[2]{1.0f, 1.0f} };
				else if (*iter == "vec3")
					uniform = new Uniform{ Uniform::Type::VECTOR3, new float[3]{1.0f, 1.0f, 1.0f} };
				else if (*iter == "vec4")
					uniform = new Uniform{ Uniform::Type::VECTOR4, new float[4]{1.0f, 1.0f, 1.0f, 1.0f} };

				std::advance(iter, 1);
				defaultUniforms.emplace(std::make_pair(*iter, uniform));
			}
		}
	}
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
	for (auto it = defaultUniforms.begin(); it != defaultUniforms.end(); it++)
		delete it->second;
}

std::string Material::getShader() const
{
	return srcShader;
}