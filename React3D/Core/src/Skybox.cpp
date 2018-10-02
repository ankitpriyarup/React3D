#include "Skybox.h"

Skybox::Skybox(const std::string& pathBack, const std::string& pathFront,
	const std::string& pathDown, const std::string& pathUp,
	const std::string& pathLeft, const std::string& pathRight)
{
	data = new float[108]
	{
		-10.0f,  10.0f, -10.0f,
		-10.0f, -10.0f, -10.0f,
		 10.0f, -10.0f, -10.0f,
		 10.0f, -10.0f, -10.0f,
		 10.0f,  10.0f, -10.0f,
		-10.0f,  10.0f, -10.0f,

		-10.0f, -10.0f,  10.0f,
		-10.0f, -10.0f, -10.0f,
		-10.0f,  10.0f, -10.0f,
		-10.0f,  10.0f, -10.0f,
		-10.0f,  10.0f,  10.0f,
		-10.0f, -10.0f,  10.0f,

		 10.0f, -10.0f, -10.0f,
		 10.0f, -10.0f,  10.0f,
		 10.0f,  10.0f,  10.0f,
		 10.0f,  10.0f,  10.0f,
		 10.0f,  10.0f, -10.0f,
		 10.0f, -10.0f, -10.0f,

		-10.0f, -10.0f,  10.0f,
		-10.0f,  10.0f,  10.0f,
		 10.0f,  10.0f,  10.0f,
		 10.0f,  10.0f,  10.0f,
		 10.0f, -10.0f,  10.0f,
		-10.0f, -10.0f,  10.0f,

		-10.0f,  10.0f, -10.0f,
		 10.0f,  10.0f, -10.0f,
		 10.0f,  10.0f,  10.0f,
		 10.0f,  10.0f,  10.0f,
		-10.0f,  10.0f,  10.0f,
		-10.0f,  10.0f, -10.0f,

		-10.0f, -10.0f, -10.0f,
		-10.0f, -10.0f,  10.0f,
		 10.0f, -10.0f, -10.0f,
		 10.0f, -10.0f, -10.0f,
		-10.0f, -10.0f,  10.0f,
		 10.0f, -10.0f,  10.0f
	};

	vertexArray = new VertexArray;
	vertexBuffer = new VertexBuffer(data, 108 * sizeof(float));

	layout = new VertexBufferLayout;
	layout->Push<float>(3);
	vertexArray->AddBuffer(*vertexBuffer, *layout);
	shader = new Shader("res/shaders/Skybox.shader");
	cubemap = new Cubemap(pathBack, pathFront, pathDown, pathUp, pathLeft, pathRight);
}

Skybox::~Skybox()
{
	delete cubemap;
	delete shader;
	delete layout;
	delete vertexBuffer;
	delete vertexArray;
	delete data;
}

void Skybox::Render(glm::mat4* _viewMatrix, glm::mat4* _projectionMatrix)
{
	glDepthFunc(GL_LEQUAL);
	shader->Bind();
	shader->SetUniformMat4f("u_view", glm::mat4(glm::mat3(*_viewMatrix)));
	shader->SetUniformMat4f("u_projection", *_projectionMatrix);
	vertexArray->Bind();
	cubemap->Bind();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDepthFunc(GL_LESS);
}
