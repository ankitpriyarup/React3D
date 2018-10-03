#pragma once
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>

class Mesh
{
private:
	std::string directory;
	void loadMesh(bool _isPerspective, const std::string& path);
	void processNode(bool _isPerspective, aiNode* node, const aiScene* scene);

public:
	struct meshData
	{
		float* data;
		unsigned int* indices;
		int dataSize;
		int indicesSize;
	};
	std::vector<meshData*> data;
	enum PrimitiveMesh { quad, cube };

	Mesh(bool _isPerspective, PrimitiveMesh _mesh);
	Mesh(bool _isPerspective, const std::string& path);
	~Mesh();

};