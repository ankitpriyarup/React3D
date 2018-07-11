#include "Window.h"
#include "EngineResources.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 540;

float positions[] =
{
	-0.5f, -0.5,
	0.5f, -0.5f,
	0.5f,  0.5f,
	-0.5f,  0.5f
};
unsigned int indices[] =
{
	0, 1, 2,
	2, 3, 0
};
VertexArray* va;
VertexBuffer* vb;
VertexBufferLayout* layout;
IndexBuffer* ib;
Shader* shader;
Renderer* renderer;

void start()
{
	va = new VertexArray;
	vb = new VertexBuffer(positions, 4 * 2 * sizeof(float));
	layout = new VertexBufferLayout;

	(*layout).Push<float>(2);
	(*va).AddBuffer(*vb, *layout);

	ib = new IndexBuffer(indices, 6);

	shader = new Shader("../Core/res/shaders/UnlitColor.shader");
	(*shader).Bind();
	(*shader).SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

	renderer = new Renderer;
}

void update()
{
	glClearColor(COLOR_DARK_R, COLOR_DARK_G, COLOR_DARK_B, COLOR_DARK_A);
	(*renderer).Draw(*va, *ib, *shader);
}

int main(void)
{
	Window::CreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "React 3D", &update, &start);

	return 0;
}