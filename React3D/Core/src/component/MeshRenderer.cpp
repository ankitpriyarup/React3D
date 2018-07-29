#include "MeshRenderer.h"

component::MeshRenderer::MeshRenderer(Material * _material, float * data, unsigned int * indices,
	unsigned int dataSize, unsigned int indicesSize)
{
	vertexArray = new VertexArray;
	vertexBuffer = new VertexBuffer(data, dataSize* sizeof(float));

	layout = new VertexBufferLayout;
	layout->Push<float>(2);
	layout->Push<float>(2);
	vertexArray->AddBuffer(*vertexBuffer, *layout);

	indexBuffer = new IndexBuffer(indices, indicesSize);

	material = _material;
	material->bind();
}

component::MeshRenderer::~MeshRenderer()
{
	delete vertexArray;
	delete vertexBuffer;
	delete layout;
	delete indexBuffer;
	delete[] data;
	delete[] indices;
}

void component::MeshRenderer::Load()
{
}

void component::MeshRenderer::Render(Renderer* _renderer)
{
	_renderer->Draw(*vertexArray, *indexBuffer, *(material->getShader()));
}

float* component::MeshRenderer::getData() const
{
	return data;
}

unsigned int* component::MeshRenderer::getIndices() const
{
	return indices;
}

Material* component::MeshRenderer::getMaterial() const
{
	return material;
}

void component::MeshRenderer::Reset()
{
}

std::string component::MeshRenderer::GetComponentName()
{
	return component::MESH_RENDERER;
}
