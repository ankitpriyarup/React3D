#include "Mesh.h"

Mesh::Mesh()
{
	data = new float[16]
	{
		-50.0f, -50.0f, 0.0f, 0.0f,
		50.0f, -50.0f, 1.0f, 0.0f,
		50.0f,  50.0f, 1.0f, 1.0f,
		-50.0f,  50.0f, 0.0f, 1.0f
	};

	indices = new unsigned int[6]
	{
		0, 1, 2,
		2, 3, 0
	};

	dataSize = 16;
	indicesSize = 6;
}

Mesh::~Mesh()
{
	delete[] data;
	delete[] indices;
}
