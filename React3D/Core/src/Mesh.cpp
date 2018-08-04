#include "Mesh.h"

Mesh::Mesh(bool _isPerspective, PrimitiveMesh _mesh)
{
	const int projectionMultiplier = (_isPerspective) ? 1 : 100;
	switch (_mesh)
	{
	case Mesh::quad:
	{
		data = new float[20]
		{
			-0.5f * projectionMultiplier, -0.5f * projectionMultiplier, 0.0f, 0.0f, 0.0f,
			 0.5f * projectionMultiplier, -0.5f * projectionMultiplier, 0.0f, 1.0f, 0.0f,
			 0.5f * projectionMultiplier,  0.5f * projectionMultiplier, 0.0f, 1.0f, 1.0f,
			-0.5f * projectionMultiplier,  0.5f * projectionMultiplier, 0.0f, 0.0f, 1.0f
		};

		indices = new unsigned int[6]
		{
			0, 1, 2,
			2, 3, 0
		};

		dataSize = 20;
		indicesSize = 6;

		break;
	}
	case Mesh::cube:
	{
		data = new float[120]
		{
			-0.5f * projectionMultiplier, -0.5f * projectionMultiplier, -0.5f * projectionMultiplier,  0.0f, 0.0f,
			 0.5f * projectionMultiplier, -0.5f * projectionMultiplier, -0.5f * projectionMultiplier,  1.0f, 0.0f,
			 0.5f * projectionMultiplier,  0.5f * projectionMultiplier, -0.5f * projectionMultiplier,  1.0f, 1.0f,
			-0.5f * projectionMultiplier,  0.5f * projectionMultiplier, -0.5f * projectionMultiplier,  0.0f, 1.0f,

			-0.5f * projectionMultiplier, -0.5f * projectionMultiplier,  0.5f * projectionMultiplier,  0.0f, 0.0f,
			 0.5f * projectionMultiplier, -0.5f * projectionMultiplier,  0.5f * projectionMultiplier,  1.0f, 0.0f,
			 0.5f * projectionMultiplier,  0.5f * projectionMultiplier,  0.5f * projectionMultiplier,  1.0f, 1.0f,
			-0.5f * projectionMultiplier,  0.5f * projectionMultiplier,  0.5f * projectionMultiplier,  0.0f, 1.0f,

			-0.5f * projectionMultiplier,  0.5f * projectionMultiplier,  0.5f * projectionMultiplier,  1.0f, 0.0f,
			-0.5f * projectionMultiplier,  0.5f * projectionMultiplier, -0.5f * projectionMultiplier,  1.0f, 1.0f,
			-0.5f * projectionMultiplier, -0.5f * projectionMultiplier, -0.5f * projectionMultiplier,  0.0f, 1.0f,
			-0.5f * projectionMultiplier, -0.5f * projectionMultiplier,  0.5f * projectionMultiplier,  0.0f, 0.0f,

			 0.5f * projectionMultiplier,  0.5f * projectionMultiplier,  0.5f * projectionMultiplier,  1.0f, 0.0f,
			 0.5f * projectionMultiplier,  0.5f * projectionMultiplier, -0.5f * projectionMultiplier,  1.0f, 1.0f,
			 0.5f * projectionMultiplier, -0.5f * projectionMultiplier, -0.5f * projectionMultiplier,  0.0f, 1.0f,
			 0.5f * projectionMultiplier, -0.5f * projectionMultiplier,  0.5f * projectionMultiplier,  0.0f, 0.0f,

			-0.5f * projectionMultiplier, -0.5f * projectionMultiplier, -0.5f * projectionMultiplier,  0.0f, 1.0f,
			 0.5f * projectionMultiplier, -0.5f * projectionMultiplier, -0.5f * projectionMultiplier,  1.0f, 1.0f,
			 0.5f * projectionMultiplier, -0.5f * projectionMultiplier,  0.5f * projectionMultiplier,  1.0f, 0.0f,
			-0.5f * projectionMultiplier, -0.5f * projectionMultiplier,  0.5f * projectionMultiplier,  0.0f, 0.0f,

			-0.5f * projectionMultiplier,  0.5f * projectionMultiplier, -0.5f * projectionMultiplier,  0.0f, 1.0f,
			 0.5f * projectionMultiplier,  0.5f * projectionMultiplier, -0.5f * projectionMultiplier,  1.0f, 1.0f,
			 0.5f * projectionMultiplier,  0.5f * projectionMultiplier,  0.5f * projectionMultiplier,  1.0f, 0.0f,
			-0.5f * projectionMultiplier,  0.5f * projectionMultiplier,  0.5f * projectionMultiplier,  0.0f, 0.0f
		};

		indices = new unsigned int[36]
		{
			0, 1, 2,
			2, 3, 0,

			4, 5, 6,
			6, 7, 4,

			8, 9, 10,
			10, 11, 8,

			12, 13, 14,
			14, 15, 12,

			16, 17, 18,
			18, 19, 16,

			20, 21, 22,
			22, 23, 20
		};

		dataSize = 120;
		indicesSize = 36;

		break;
	}
	default:
		break;
	}
}

Mesh::~Mesh()
{
	delete[] data;
	delete[] indices;
}
