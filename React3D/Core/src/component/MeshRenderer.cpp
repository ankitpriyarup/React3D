#include "MeshRenderer.h"

component::MeshRenderer::MeshRenderer(Material* _material, Mesh* _mesh)
	: material(_material), mesh(_mesh)
{
	vertexArray = new VertexArray;
	vertexBuffer = new VertexBuffer(mesh->data, mesh->dataSize * sizeof(float));

	layout = new VertexBufferLayout;
	layout->Push<float>(2);
	layout->Push<float>(2);
	vertexArray->AddBuffer(*vertexBuffer, *layout);
	indexBuffer = new IndexBuffer(mesh->indices, mesh->indicesSize);
	material->bind();
}

component::MeshRenderer::~MeshRenderer()
{
	delete vertexArray;
	delete vertexBuffer;
	delete layout;
	delete indexBuffer;
	delete mesh;
}

void component::MeshRenderer::Load()
{
}

void component::MeshRenderer::Render(Renderer* _renderer)
{
	_renderer->Draw(*vertexArray, *indexBuffer, *(material->getShader()));
}

Mesh * component::MeshRenderer::getMesh() const
{
	return mesh;
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
