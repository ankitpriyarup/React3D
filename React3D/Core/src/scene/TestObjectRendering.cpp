#include "TestObjectRendering.h"

namespace scene
{
	scene::TestObjectRendering::TestObjectRendering(int* _width, int* _height) :
		Scene(Projection::Perspective, _width, _height)
	{
		texMat = new Material("res/shaders/UnlitTexture.shader", "res/textures/container.png");
		float* col = (float*)texMat->defaultUniforms["u_color"]->value;
		col[0] = 1.0f;
		col[1] = 1.0f;
		col[2] = 0.0f;
		col[3] = 1.0f;
		float* blend = (float*)texMat->defaultUniforms["u_blend"]->value;
		*blend = 0.5f;

		AddGameObject("test", glm::vec3(5, 0, -10))
			->AddMeshRenderer(new component::MeshRenderer(texMat,
				new Mesh(projection == Projection::Perspective, Mesh::PrimitiveMesh::cube)));

		AddGameObject("test2", glm::vec3(-5, 0, -10))
			->AddMeshRenderer(new component::MeshRenderer(texMat,
				new Mesh(projection == Projection::Perspective, Mesh::PrimitiveMesh::cube)));

		AddGameObject("test3", glm::vec3(0, 0, -10))
			->AddMeshRenderer(new component::MeshRenderer(texMat,
				new Mesh(projection == Projection::Perspective, Mesh::PrimitiveMesh::cube)));
	}

	scene::TestObjectRendering::~TestObjectRendering()
	{
		delete texMat;
	}

	int incrementRot = 0;
	void TestObjectRendering::OnUpdate(double deltaTime)
	{
		Scene::OnUpdate(deltaTime);

		component::Transform* transform =
			(component::Transform*) gameObjects["test"]->GetComponent(component::TRANSFORM);

		transform->setRotation(glm::vec4(0, 1, 1, ++incrementRot * 0.001f));
		transform->setScale(glm::vec3(2.0f, 2.0f, 2.0f));
		transform->Update();
	}

	void TestObjectRendering::OnRender(Renderer* _renderer)
	{
		Scene::OnRender(_renderer);
	}
}