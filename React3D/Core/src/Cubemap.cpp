#include "Cubemap.h"
#include "stb_image/stb_image.h"

Cubemap::Cubemap(const std::string & pathBack, const std::string & pathFront,
	const std::string & pathDown, const std::string & pathUp,
	const std::string & pathLeft, const std::string & pathRight)
{
	faces[0].m_FilePath = pathBack;
	faces[1].m_FilePath = pathFront;
	faces[2].m_FilePath = pathDown;
	faces[3].m_FilePath = pathUp;
	faces[4].m_FilePath = pathLeft;
	faces[5].m_FilePath = pathRight;

	GLCall(glGenTextures(1, &textureID));
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, textureID));

	//Face 0
	faces[0].m_LocalBuffer = stbi_load(faces[0].m_FilePath.c_str(),
		&faces[0].m_Width, &faces[0].m_Height, &faces[0].m_BPP, 4);
	GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA8, faces[0].m_Width, faces[0].m_Height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, faces[0].m_LocalBuffer));
	if (faces[0].m_LocalBuffer)
		stbi_image_free(faces[0].m_LocalBuffer);
	//Face 1
	faces[1].m_LocalBuffer = stbi_load(faces[1].m_FilePath.c_str(),
		&faces[1].m_Width, &faces[1].m_Height, &faces[1].m_BPP, 4);
	GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA8, faces[1].m_Width, faces[1].m_Height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, faces[1].m_LocalBuffer));
	if (faces[1].m_LocalBuffer)
		stbi_image_free(faces[1].m_LocalBuffer);
	//Face 2
	faces[2].m_LocalBuffer = stbi_load(faces[2].m_FilePath.c_str(),
		&faces[2].m_Width, &faces[2].m_Height, &faces[2].m_BPP, 4);
	GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA8, faces[2].m_Width, faces[2].m_Height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, faces[2].m_LocalBuffer));
	if (faces[2].m_LocalBuffer)
		stbi_image_free(faces[2].m_LocalBuffer);
	//Face 3
	faces[3].m_LocalBuffer = stbi_load(faces[3].m_FilePath.c_str(),
		&faces[3].m_Width, &faces[3].m_Height, &faces[3].m_BPP, 4);
	GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA8, faces[3].m_Width, faces[3].m_Height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, faces[3].m_LocalBuffer));
	if (faces[3].m_LocalBuffer)
		stbi_image_free(faces[3].m_LocalBuffer);
	//Face 4
	faces[4].m_LocalBuffer = stbi_load(faces[4].m_FilePath.c_str(),
		&faces[4].m_Width, &faces[4].m_Height, &faces[4].m_BPP, 4);
	GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA8, faces[4].m_Width, faces[4].m_Height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, faces[4].m_LocalBuffer));
	if (faces[4].m_LocalBuffer)
		stbi_image_free(faces[4].m_LocalBuffer);
	//Face 5
	faces[5].m_LocalBuffer = stbi_load(faces[5].m_FilePath.c_str(),
		&faces[5].m_Width, &faces[5].m_Height, &faces[5].m_BPP, 4);
	GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA8, faces[5].m_Width, faces[5].m_Height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, faces[5].m_LocalBuffer));
	if (faces[5].m_LocalBuffer)
		stbi_image_free(faces[5].m_LocalBuffer);

	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
}

Cubemap::~Cubemap()
{
	GLCall(glDeleteTextures(1, &textureID));
}

void Cubemap::Bind() const
{
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, textureID));
}

void Cubemap::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}