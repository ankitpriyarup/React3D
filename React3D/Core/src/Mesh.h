#pragma once

class Mesh
{
public:
	float* data;
	unsigned int* indices;
	int dataSize;
	int indicesSize;
	enum PrimitiveMesh { quad, cube };

	Mesh(PrimitiveMesh _mesh);
	~Mesh();
};