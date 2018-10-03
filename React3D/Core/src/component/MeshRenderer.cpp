#include "MeshRenderer.h"

component::MeshRenderer::MeshRenderer(Material* _material, Mesh* _mesh)
	: material(_material), mesh(_mesh)
{
	for (unsigned int i = 0; i < mesh->data.size(); i++)
	{
		meshData.push_back(new vertex);
		meshData[i]->vertexBuffer = new VertexBuffer(mesh->data[i]->data,
			mesh->data[i]->dataSize * sizeof(float));
		meshData[i]->vertexArray = new VertexArray;
		meshData[i]->layout = new VertexBufferLayout;
		meshData[i]->layout->Push<float>(3);
		meshData[i]->layout->Push<float>(2);
		meshData[i]->layout->Push<float>(3);
		meshData[i]->vertexArray->AddBuffer(*(meshData[i]->vertexBuffer),
			*(meshData[i]->layout));
		meshData[i]->indexBuffer = new IndexBuffer(mesh->data[i]->indices,
			mesh->data[i]->indicesSize);
	}

	shader = new Shader(material->getShader());
	shader->Bind();
	if (material->textures.size() > 0)
	{
		material->textures[0]->Bind(0);
		shader->SetUniform1i("u_albedo", 0);
	}

	auto fit = material->defaultUniforms.find("u_normalmap");
	if (fit != material->defaultUniforms.end())
	{
		material->textures[1]->Bind(1);
		shader->SetUniform1i("u_normalmap", 1);
	}
	for (auto it = material->defaultUniforms.begin(); it != material->defaultUniforms.end(); it++)
		shader->SetUniform(it->first, *it->second);
}

component::MeshRenderer::~MeshRenderer()
{
	for (unsigned int i = 0; i < meshData.size(); i++)
	{
		delete meshData[i]->vertexArray;
		delete meshData[i]->vertexBuffer;
		delete meshData[i]->layout;
		delete meshData[i]->indexBuffer;
	}
	delete mesh;
	delete shader;
}

void component::MeshRenderer::Update()
{
}

void component::MeshRenderer::Render(Renderer* _renderer)
{
	for (unsigned int i = 0; i < meshData.size(); i++)
		_renderer->Draw(*(meshData[i]->vertexArray), *(meshData[i]->indexBuffer), *shader);
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
