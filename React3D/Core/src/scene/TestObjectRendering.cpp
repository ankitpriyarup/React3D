#include "TestObjectRendering.h"

namespace scene
{
	scene::TestObjectRendering::TestObjectRendering(int* _width, int* _height) : 
		width(_width), height(_height)
	{
		texMat = new Material("res/shaders/Diffuse.shader", "res/textures/icon_react_large.png");

		GameObject* gb = new GameObject(_width, _height);
		gb->AddMeshRenderer(new component::MeshRenderer(texMat, new Mesh()));
		gameObjects.emplace_back(gb);
	}

	scene::TestObjectRendering::~TestObjectRendering()
	{
		for (GameObject* gameObject : gameObjects)
			delete gameObject;

		delete texMat;
	}

	void TestObjectRendering::OnUpdate(float deltaTime)
	{
		component::Transform* transform = 
			(component::Transform*) gameObjects[0]->GetComponent(component::TRANSFORM);

		glm::vec3 curPos = transform->getPosition();
		transform->setPosition(glm::vec3(curPos.x + 1, curPos.y + 1, curPos.z));
	}

	void TestObjectRendering::OnRender(Renderer* _renderer)
	{
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

		for (GameObject* gameObject : gameObjects)
			gameObject->Render(_renderer);
	}
}