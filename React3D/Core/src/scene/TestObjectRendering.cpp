#include "TestObjectRendering.h"

namespace scene
{
	scene::TestObjectRendering::TestObjectRendering(int* _width, int* _height) :
		Scene(Projection::Perspective, _width, _height)
	{
		texMat = new Material("res/shaders/BumpedSpecular.shader", "res/textures/container.png");
		texMat->assignNormalMap("res/textures/container_specular.png");
		float* col = (float*)texMat->defaultUniforms["u_color"]->value;
		col[0] = 1.0f;
		col[1] = 0.0f;
		col[2] = 0.0f;
		col[3] = 1.0f;
		float* blend = (float*)texMat->defaultUniforms["u_blend"]->value;
		*blend = 0.5f;
		float* shininess = (float*)texMat->defaultUniforms["u_shininess"]->value;
		*shininess = 12.0f;

		AddGameObject("Crate1", glm::vec3(0.0f, 0.0f, -10.0f))
			->AddMeshRenderer(new component::MeshRenderer(texMat,
				new Mesh(projection == Projection::Perspective, Mesh::PrimitiveMesh::cube)));
		AddGameObject("Crate2", glm::vec3(-2.0f, 0.0f, -10.0f), glm::vec4(0.0f, 1.0f, 0.0f, -0.35f))
			->AddMeshRenderer(new component::MeshRenderer(texMat,
				new Mesh(projection == Projection::Perspective, Mesh::PrimitiveMesh::cube)));

		AddGameObject("Light" + std::to_string(++pointLightCount), glm::vec3(0.0f, 0.0f, -12.0f))
			->AddLightSource(new component::LightSource(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.05f, 0.05f, 0.05f),
				glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(0.5f, 0.5f, 0.5f), 1.0f, 0.09f, 0.032f));
		AddGameObject("Light" + std::to_string(++pointLightCount), glm::vec3(-2.0f, -2.0f, -10.0f))
			->AddLightSource(new component::LightSource(glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(0.1f, 0.1f, 0.1f),
				glm::vec3(1.6f, 1.6f, 1.6f), glm::vec3(1.0f, 1.0f, 1.0f), 2.0f, 0.2f, 0.06f));
		SetSpotLight(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),
			glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, 12.5f, 15.0f);
		UpdateDirectionalLight(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-1.0f, -1.0f, 0.0f),
			glm::vec3(0.03f, 0.03f, 0.03f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.2f, 0.2f, 0.2f));
		performLightningCalculations();
	}

	scene::TestObjectRendering::~TestObjectRendering()
	{
		delete texMat;
	}

	void TestObjectRendering::OnUpdate(double deltaTime)
	{
		Scene::OnUpdate(deltaTime);
	}

	void TestObjectRendering::OnRender(Renderer* _renderer)
	{
		Scene::OnRender(_renderer);
	}
}