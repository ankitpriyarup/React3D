#pragma once
struct Uniform
{
	enum Type { TEXTURE2D, FLOAT, INT, VECTOR2, VECTOR3, VECTOR4 };

	Type type;
	void* value;
};