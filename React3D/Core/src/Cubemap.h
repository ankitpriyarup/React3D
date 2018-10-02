#pragma once
#include "Renderer.h"
#include <GL/glew.h>
#include <vector>

class Cubemap
{
private:
	struct sepTextures
	{
		unsigned int m_RendererID;
		std::string m_FilePath;
		unsigned char* m_LocalBuffer = nullptr;
		int m_Width = 0;
		int m_Height = 0;
		int m_BPP = 0;
	};
	sepTextures faces[6];
	unsigned int textureID;

public:
	Cubemap(const std::string& pathBack, const std::string& pathFront,
		const std::string& pathDown, const std::string& pathUp,
		const std::string& pathLeft, const std::string& pathRight);
	~Cubemap();
	void Bind() const;
	void Unbind() const;
};