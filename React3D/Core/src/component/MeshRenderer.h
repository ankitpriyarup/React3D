#pragma once
#include "Component.h"
#include "Mesh.h"
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
		Mesh* mesh;
		Material* material;
		VertexArray* vertexArray;
		VertexBuffer* vertexBuffer;
		VertexBufferLayout* layout;
		IndexBuffer* indexBuffer;

	public:
		MeshRenderer(Material* _material, Mesh* _mesh);
		~MeshRenderer();
		void Load();
		void Render(Renderer* _renderer) override;
		Mesh* getMesh() const;
		Material* getMaterial() const;
		void Reset() override;
		std::string GetComponentName() override;
	};
}