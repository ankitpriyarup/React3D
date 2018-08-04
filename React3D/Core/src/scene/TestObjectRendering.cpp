#include "TestObjectRendering.h"

namespace scene
{
	scene::TestObjectRendering::TestObjectRendering(int* _width, int* _height) : 
		width(_width), height(_height)
	{
		projectionMatrix = new glm::mat4(glm::ortho(0.0f, (float)*_width, 0.0f, (float)*_height, -500.0f, 500.0f));
		//projectionMatrix = new glm::mat4(glm::perspective(45.0f, (float)*_width / (float)*_height, 0.0f, 1000.0f));

		texMat = new Material("res/shaders/Diffuse.shader", "res/textures/icon_react_large.png");

		GameObject* gb = new GameObject(projectionMatrix);
		gb->AddMeshRenderer(new component::MeshRenderer(texMat, new Mesh(Mesh::PrimitiveMesh::quad)));
		gameObjects.emplace_back(gb);
	}

	scene::TestObjectRendering::~TestObjectRendering()
	{
		for (GameObject* gameObject : gameObjects)
			delete gameObject;

		delete texMat;
		delete projectionMatrix;
	}

	int logoIncrementX = 1;
	int logoIncrementY = 1;
	int incrementRot = 0;
	void TestObjectRendering::OnUpdate(float deltaTime)
	{
		component::Transform* transform = 
			(component::Transform*) gameObjects[0]->GetComponent(component::TRANSFORM);

		glm::vec3 curPos = transform->getPosition();
		logoIncrementX *= ((int)curPos.x > (*width - 50) || curPos.x < 0) ? -1 : 1;
		logoIncrementY *= ((int)curPos.y > (*height - 100) || curPos.y < 0) ? -1 : 1;
		incrementRot++;

		transform->setPosition(glm::vec3(curPos.x + logoIncrementX , curPos.y + logoIncrementY, curPos.z));
		transform->setRotation(glm::vec4(0, 0, 1, incrementRot * 0.01f));
		transform->setScale(glm::vec3(2.0f, 2.0f, 2.0f));
		transform->UpdateTransform();
	}

	void TestObjectRendering::OnRender(Renderer* _renderer)
	{
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

		for (GameObject* gameObject : gameObjects)
			gameObject->Render(_renderer);
	}
}