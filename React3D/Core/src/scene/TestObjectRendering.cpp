#include "TestObjectRendering.h"

namespace scene
{
	scene::TestObjectRendering::TestObjectRendering(int* _width, int* _height) :
		Scene(Projection::Perspective, _width, _height)
	{
		texMat = new Material("res/shaders/Diffuse.shader", "res/textures/container.png");
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

		AddGameObject("lightSource", glm::vec3(10, 10, 1))
			->AddLightSource(new component::LightSource(glm::vec3(1.0f, 1.0f, 1.0f)));

		AddGameObject("crate1", glm::vec3(0, 0, -10))
			->AddMeshRenderer(new component::MeshRenderer(texMat,
				new Mesh(projection == Projection::Perspective, Mesh::PrimitiveMesh::cube)));

		AddGameObject("crate2", glm::vec3(-2, 0, -10), glm::vec4(0, 1, 0, -0.35f))
			->AddMeshRenderer(new component::MeshRenderer(texMat,
				new Mesh(projection == Projection::Perspective, Mesh::PrimitiveMesh::cube)));

		//TEST TO REMOVE
		component::MeshRenderer* rend1 =
			(component::MeshRenderer*) gameObjects["crate1"]->GetComponent(component::MESH_RENDERER);
		component::MeshRenderer* rend2 =
			(component::MeshRenderer*) gameObjects["crate2"]->GetComponent(component::MESH_RENDERER);

		rend1->getShader()->Bind();
		rend1->getShader()->SetUniform3f("x_dirLight.color", 1.0f, 1.0f, 1.0f);
		rend1->getShader()->SetUniform3f("x_dirLight.direction", -1.0f, -1.0f, 0.0f);
		rend1->getShader()->SetUniform3f("x_dirLight.ambient", 0.03f, 0.03f, 0.03f);
		rend1->getShader()->SetUniform3f("x_dirLight.diffuse", 0.5f, 0.5f, 0.5f);
		rend1->getShader()->SetUniform3f("x_dirLight.specular", 0.2f, 0.2f, 0.2f);
		rend1->getShader()->SetUniform1i("x_pointLightsCount", 2);
		rend1->getShader()->SetUniform3f("x_pointLights[0].color", 0.0f, 1.0f, 0.0f);
		rend1->getShader()->SetUniform3f("x_pointLights[0].position", 0.0f, 0.0f, -12.0f);
		rend1->getShader()->SetUniform3f("x_pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
		rend1->getShader()->SetUniform3f("x_pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
		rend1->getShader()->SetUniform3f("x_pointLights[0].specular", 0.5f, 0.5f, 0.5f);
		rend1->getShader()->SetUniform1f("x_pointLights[0].constant", 1.0f);
		rend1->getShader()->SetUniform1f("x_pointLights[0].linear", 0.09f);
		rend1->getShader()->SetUniform1f("x_pointLights[0].quadratic", 0.032f);
		rend1->getShader()->SetUniform3f("x_pointLights[1].color", 0.0f, 1.0f, 1.0f);
		rend1->getShader()->SetUniform3f("x_pointLights[1].position", -2.0f, -2.0f, -10.0f);
		rend1->getShader()->SetUniform3f("x_pointLights[1].ambient", 0.1f, 0.1f, 0.1f);
		rend1->getShader()->SetUniform3f("x_pointLights[1].diffuse", 1.6f, 1.6f, 1.6f);
		rend1->getShader()->SetUniform3f("x_pointLights[1].specular", 1.0f, 1.0f, 1.0f);
		rend1->getShader()->SetUniform1f("x_pointLights[1].constant", 2.0f);
		rend1->getShader()->SetUniform1f("x_pointLights[1].linear", 0.2f);
		rend1->getShader()->SetUniform1f("x_pointLights[1].quadratic", 0.06f);
		rend1->getShader()->SetUniform3f("x_spotLight.color", 1.0f, 1.0f, 1.0f);
		rend1->getShader()->SetUniform3f("x_spotLight.ambient", 0.0f, 0.0f, 0.0f);
		rend1->getShader()->SetUniform3f("x_spotLight.diffuse", 1.0f, 1.0f, 1.0f);
		rend1->getShader()->SetUniform3f("x_spotLight.specular", 1.0f, 1.0f, 1.0f);
		rend1->getShader()->SetUniform1f("x_spotLight.constant", 1.0f);
		rend1->getShader()->SetUniform1f("x_spotLight.linear", 0.09f);
		rend1->getShader()->SetUniform1f("x_spotLight.quadratic", 0.032f);
		rend1->getShader()->SetUniform1f("x_spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		rend1->getShader()->SetUniform1f("x_spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

		rend2->getShader()->Bind();
		rend2->getShader()->SetUniform3f("x_dirLight.color", 1.0f, 1.0f, 1.0f);
		rend2->getShader()->SetUniform3f("x_dirLight.direction", -2.0f, 0.0f, -12.0f);
		rend2->getShader()->SetUniform3f("x_dirLight.ambient", 0.03f, 0.03f, 0.03f);
		rend2->getShader()->SetUniform3f("x_dirLight.diffuse", 0.5f, 0.5f, 0.5f);
		rend2->getShader()->SetUniform3f("x_dirLight.specular", 0.2f, 0.2f, 0.2f);
		rend2->getShader()->SetUniform1i("x_pointLightsCount", 2);
		rend2->getShader()->SetUniform3f("x_pointLights[0].color", 0.0f, 1.0f, 0.0f);
		rend2->getShader()->SetUniform3f("x_pointLights[0].position", 0.0f, -2.0f, -10.0f);
		rend2->getShader()->SetUniform3f("x_pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
		rend2->getShader()->SetUniform3f("x_pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
		rend2->getShader()->SetUniform3f("x_pointLights[0].specular", 0.5f, 0.5f, 0.5f);
		rend2->getShader()->SetUniform1f("x_pointLights[0].constant", 1.0f);
		rend2->getShader()->SetUniform1f("x_pointLights[0].linear", 0.09f);
		rend2->getShader()->SetUniform1f("x_pointLights[0].quadratic", 0.032f);
		rend2->getShader()->SetUniform3f("x_pointLights[1].color", 0.0f, 1.0f, 1.0f);
		rend2->getShader()->SetUniform3f("x_pointLights[1].position", -2.0f, -2.0f, -10.0f);
		rend2->getShader()->SetUniform3f("x_pointLights[1].ambient", 0.1f, 0.1f, 0.1f);
		rend2->getShader()->SetUniform3f("x_pointLights[1].diffuse", 1.6f, 1.6f, 1.6f);
		rend2->getShader()->SetUniform3f("x_pointLights[1].specular", 1.0f, 1.0f, 1.0f);
		rend2->getShader()->SetUniform1f("x_pointLights[1].constant", 2.0f);
		rend2->getShader()->SetUniform1f("x_pointLights[1].linear", 0.2f);
		rend2->getShader()->SetUniform1f("x_pointLights[1].quadratic", 0.06f);
		rend2->getShader()->SetUniform3f("x_spotLight.color", 1.0f, 1.0f, 1.0f);
		rend2->getShader()->SetUniform3f("x_spotLight.ambient", 0.0f, 0.0f, 0.0f);
		rend2->getShader()->SetUniform3f("x_spotLight.diffuse", 1.0f, 1.0f, 1.0f);
		rend2->getShader()->SetUniform3f("x_spotLight.specular", 1.0f, 1.0f, 1.0f);
		rend2->getShader()->SetUniform1f("x_spotLight.constant", 1.0f);
		rend2->getShader()->SetUniform1f("x_spotLight.linear", 0.09f);
		rend2->getShader()->SetUniform1f("x_spotLight.quadratic", 0.032f);
		rend2->getShader()->SetUniform1f("x_spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		rend2->getShader()->SetUniform1f("x_spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
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