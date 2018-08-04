#include "TestObjectRendering.h"

namespace scene
{
	scene::TestObjectRendering::TestObjectRendering(int* _width, int* _height) :
		Scene(Projection::Perspective, _width, _height)
	{
		texMat = new Material("res/shaders/UnlitTexture.shader", "res/textures/icon_react_large.png");

		AddGameObject("test", glm::vec3(5, 0, -10))
			->AddMeshRenderer(new component::MeshRenderer(texMat,
				new Mesh(projection == Projection::Perspective, Mesh::PrimitiveMesh::cube)));

		AddGameObject("tes2t", glm::vec3(-5, 0, -10))
			->AddMeshRenderer(new component::MeshRenderer(texMat,
				new Mesh(projection == Projection::Perspective, Mesh::PrimitiveMesh::cube)));
	}

	scene::TestObjectRendering::~TestObjectRendering()
	{
		delete texMat;
	}

	int logoIncrementX = 1;
	int logoIncrementY = 1;
	int incrementRot = 0;
	void TestObjectRendering::OnUpdate(float deltaTime)
	{
		component::Transform* transform =
			(component::Transform*) gameObjects["test"]->GetComponent(component::TRANSFORM);

		glm::vec3 curPos = transform->getPosition();
		logoIncrementX *= ((int)curPos.x > (*width - 50) || curPos.x < 0) ? -1 : 1;
		logoIncrementY *= ((int)curPos.y >(*height - 100) || curPos.y < 0) ? -1 : 1;
		incrementRot++;

		//transform->setPosition(glm::vec3(curPos.x + logoIncrementX , curPos.y + logoIncrementY, curPos.z));
		transform->setRotation(glm::vec4(0, 1, 1, incrementRot * 0.01f));
		transform->setScale(glm::vec3(2.0f, 2.0f, 2.0f));
		transform->Update();
	}

	void TestObjectRendering::OnRender(Renderer* _renderer)
	{
		Scene::OnRender(_renderer);
	}
}