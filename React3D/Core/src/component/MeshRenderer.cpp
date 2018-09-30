#include "MeshRenderer.h"

component::MeshRenderer::MeshRenderer(Material* _material, Mesh* _mesh)
	: material(_material), mesh(_mesh)
{
	vertexArray = new VertexArray;
	vertexBuffer = new VertexBuffer(mesh->data, mesh->dataSize * sizeof(float));

	layout = new VertexBufferLayout;
	layout->Push<float>(3);
	layout->Push<float>(2);
	vertexArray->AddBuffer(*vertexBuffer, *layout);
	indexBuffer = new IndexBuffer(mesh->indices, mesh->indicesSize);

	shader = new Shader(material->getShader());
	shader->Bind();
	if (material->textures.size() > 0)
	{
		material->textures[0]->Bind(0);
		shader->SetUniform1i("u_albedo", 0);
	}
	for (auto it = material->defaultUniforms.begin(); it != material->defaultUniforms.end(); it++)
		shader->SetUniform(it->first, *it->second);
}

component::MeshRenderer::~MeshRenderer()
{
	delete vertexArray;
	delete vertexBuffer;
	delete layout;
	delete indexBuffer;
	delete mesh;
	delete shader;
}

void component::MeshRenderer::Update()
{
}

void component::MeshRenderer::Render(Renderer* _renderer)
{
	_renderer->Draw(*vertexArray, *indexBuffer, *(shader));
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

Shader * component::MeshRenderer::getShader() const
{
	return shader;
}
