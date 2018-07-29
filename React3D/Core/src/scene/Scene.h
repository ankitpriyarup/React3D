#pragma once
#include "Renderer.h"
#include "GameObject.h"
#include "component/Component.h"
#include "component/Transform.h"
#include "component/MeshRenderer.h"

namespace scene
{
	class Scene
	{
	public:
		Scene() { };
		virtual ~Scene() { };

		virtual void OnUpdate(float deltaTime) { }
		virtual void OnRender(Renderer* _renderer) { }
	};
}