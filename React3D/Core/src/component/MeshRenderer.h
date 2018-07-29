#pragma once
#include "Component.h"
#include "Material.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"

namespace component
{
	static std::string MESH_RENDERER = "MeshRenderer";

	class MeshRenderer : public Component
	{
	private:
		float* data;
		unsigned int* indices;
		Material* material;
		VertexArray* vertexArray;
		VertexBuffer* vertexBuffer;
		VertexBufferLayout* layout;
		IndexBuffer* indexBuffer;

	public:
		MeshRenderer(Material* _material, float* data, unsigned int* indices,
			unsigned int dataSize, unsigned int indicesSize);
		~MeshRenderer();
		void Load();
		void Render(Renderer* _renderer) override;
		float* getData() const;
		unsigned int* getIndices() const;
		Material* getMaterial() const;
		void Reset() override;
		std::string GetComponentName() override;
	};
}