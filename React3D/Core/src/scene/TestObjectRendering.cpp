#include "TestObjectRendering.h"

namespace scene
{
	scene::TestObjectRendering::TestObjectRendering(glm::mat4& _projectionMatrix) : projectionMatrix(_projectionMatrix)
	{
		texMat = new Material("res/shaders/Diffuse.shader", "res/textures/icon_react_large.png");

		GameObject* gb = new GameObject(projectionMatrix);
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
		for (GameObject* gameObject : gameObjects)
			gameObject->Render(_renderer);
	}
}