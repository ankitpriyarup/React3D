#pragma once
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "Cubemap.h"

class Skybox
{
private:
	float* data;
	VertexArray * vertexArray;
	VertexBuffer* vertexBuffer;
	VertexBufferLayout* layout;
	Shader* shader;
	Cubemap* cubemap;

public:
	Skybox(const std::string& pathBack, const std::string& pathFront,
		const std::string& pathDown, const std::string& pathUp,
		const std::string& pathLeft, const std::string& pathRight);
	~Skybox();
	void Render(glm::mat4* _viewMatrix, glm::mat4* _projectionMatrix);
};