#pragma once
#include <iostream>
#include "Renderer.h"

class GameObject;

namespace component
{
	class Component
	{
	public:
		GameObject* gameObject;

		Component() { };
		virtual ~Component() { };
		virtual void Update() { };
		virtual void Reset() { };
		virtual void Render(Renderer* _renderer) { }
		virtual std::string GetComponentName() { return ""; };
	};
}