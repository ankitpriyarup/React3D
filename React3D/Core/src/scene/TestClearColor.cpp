#include "TestClearColor.h"

namespace scene
{
	scene::TestClearColor::TestClearColor(glm::mat4& _projectionMatrix)
	{
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GLCall(glEnable(GL_BLEND));

		texMat = new Material("res/shaders/Diffuse.shader", "res/textures/pikachu.png");

		GameObject* gb = new GameObject(_projectionMatrix);
		float* data = new float[16]
		{
			-50.0f, -50.0f, 0.0f, 0.0f,
			 50.0f, -50.0f, 1.0f, 0.0f,
			 50.0f,  50.0f, 1.0f, 1.0f,
			-50.0f,  50.0f, 0.0f, 1.0f
		};
		unsigned int* indices = new unsigned int[6]
		{
			0, 1, 2,
			2, 3, 0
		};
		gb->AddMeshRenderer(new component::MeshRenderer(texMat, data, indices, 16, 6));

		gameObjects.emplace_back(gb);
	}

	scene::TestClearColor::~TestClearColor()
	{
		for (GameObject* gameObject : gameObjects)
			delete gameObject;

		delete texMat;
	}

	void TestClearColor::OnUpdate(float deltaTime)
	{
	}

	void TestClearColor::OnRender(Renderer* _renderer)
	{
		for (GameObject* gameObject : gameObjects)
			gameObject->Render(_renderer);
	}
}