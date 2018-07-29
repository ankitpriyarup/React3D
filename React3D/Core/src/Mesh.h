#pragma once

class Mesh
{
public:
	float* data;
	unsigned int* indices;
	int dataSize;
	int indicesSize;

	Mesh();
	~Mesh();
};