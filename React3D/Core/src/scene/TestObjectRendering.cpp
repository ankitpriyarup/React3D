#include "TestObjectRendering.h"

namespace scene
{
	scene::TestObjectRendering::TestObjectRendering(int* _width, int* _height) :
		Scene(Projection::Perspective, _width, _height)
	{
		texMat = new Material("res/shaders/BumpSpecular.shader", "res/textures/container.png");
		texMat->assignNormalMap("res/textures/container_specular.png");
		float* col = (float*)texMat->defaultUniforms["u_color"]->value;
		col[0] = 1.0f;
		col[1] = 0.0f;
		col[2] = 0.0f;
		col[3] = 1.0f;
		float* blend = (float*)texMat->defaultUniforms["u_blend"]->value;
		*blend = 0.5f;
		float* ambience = (float*)texMat->defaultUniforms["u_ambience"]->value;
		*ambience = 0.8f;
		float* specular = (float*)texMat->defaultUniforms["u_specular"]->value;
		*specular = 3.0f;

		AddGameObject("lightSource", glm::vec3(10, 10, 1))
			->AddLightSource(new component::LightSource(glm::vec3(1.0f, 1.0f, 1.0f)));

		AddGameObject("test", glm::vec3(5, 0, -10))
			->AddMeshRenderer(new component::MeshRenderer(texMat,
				new Mesh(projection == Projection::Perspective, Mesh::PrimitiveMesh::cube)));

		AddGameObject("test3", glm::vec3(0, 0, -10))
			->AddMeshRenderer(new component::MeshRenderer(texMat,
				new Mesh(projection == Projection::Perspective, Mesh::PrimitiveMesh::cube)));

		AddGameObject("test2", glm::vec3(-5, 0, -10))
			->AddMeshRenderer(new component::MeshRenderer(texMat,
				new Mesh(projection == Projection::Perspective, Mesh::PrimitiveMesh::cube)));

		//TEST
		component::MeshRenderer* rend1 =
			(component::MeshRenderer*) gameObjects["test"]->GetComponent(component::MESH_RENDERER);
		component::MeshRenderer* rend2 =
			(component::MeshRenderer*) gameObjects["test2"]->GetComponent(component::MESH_RENDERER);
		component::MeshRenderer* rend3 =
			(component::MeshRenderer*) gameObjects["test3"]->GetComponent(component::MESH_RENDERER);
		rend1->getShader()->Bind();
		rend1->getShader()->SetUniform3f("lightPos", 10, 10, 1);
		rend1->getShader()->SetUniform3f("lightColor", 1.0f, 1.0f, 1.0f);
		rend2->getShader()->Bind();
		rend2->getShader()->SetUniform3f("lightPos", 10, 10, 1);
		rend2->getShader()->SetUniform3f("lightColor", 1.0f, 1.0f, 1.0f);
		rend3->getShader()->Bind();
		rend3->getShader()->SetUniform3f("lightPos", 10, 10, 1);
		rend3->getShader()->SetUniform3f("lightColor", 1.0f, 1.0f, 1.0f);
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