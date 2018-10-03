#include "Mesh.h"

void Mesh::loadMesh(bool _isPerspective, const std::string & path)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return;
	}
	directory = path.substr(0, path.find_last_of('/'));
	processNode(_isPerspective, scene->mRootNode, scene);
}

void Mesh::processNode(bool _isPerspective, aiNode * node, const aiScene * scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{

		}
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
		processNode(_isPerspective, node->mChildren[i], scene);
}

Mesh::Mesh(bool _isPerspective, PrimitiveMesh _mesh)
{
	const int projMul = (_isPerspective) ? 1 : 100;
	switch (_mesh)
	{
	case Mesh::quad:
	{
		data.push_back(new meshData);
		data[0]->data = new float[32]
		{
			-0.5f * projMul, -0.5f * projMul, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			 0.5f * projMul, -0.5f * projMul, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			 0.5f * projMul,  0.5f * projMul, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.5f * projMul,  0.5f * projMul, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
		};

		data[0]->indices = new unsigned int[6]
		{
			0, 1, 2,
			2, 3, 0
		};

		data[0]->dataSize = 32;
		data[0]->indicesSize = 6;

		break;
	}
	case Mesh::cube:
	{
		data.push_back(new meshData);
		data[0]->data = new float[192]
		{
			-0.5f * projMul, -0.5f * projMul, -0.5f * projMul,  0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
			 0.5f * projMul, -0.5f * projMul, -0.5f * projMul,  1.0f, 0.0f,  0.0f,  0.0f, -1.0f,
			 0.5f * projMul,  0.5f * projMul, -0.5f * projMul,  1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
			-0.5f * projMul,  0.5f * projMul, -0.5f * projMul,  0.0f, 1.0f,  0.0f,  0.0f, -1.0f,

			-0.5f * projMul, -0.5f * projMul,  0.5f * projMul,  0.0f, 0.0f,  0.0f,  0.0f,  1.0f,
			 0.5f * projMul, -0.5f * projMul,  0.5f * projMul,  1.0f, 0.0f,  0.0f,  0.0f,  1.0f,
			 0.5f * projMul,  0.5f * projMul,  0.5f * projMul,  1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
			-0.5f * projMul,  0.5f * projMul,  0.5f * projMul,  0.0f, 1.0f,  0.0f,  0.0f,  1.0f,

			-0.5f * projMul,  0.5f * projMul,  0.5f * projMul,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
			-0.5f * projMul,  0.5f * projMul, -0.5f * projMul,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
			-0.5f * projMul, -0.5f * projMul, -0.5f * projMul,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
			-0.5f * projMul, -0.5f * projMul,  0.5f * projMul,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,

			 0.5f * projMul,  0.5f * projMul,  0.5f * projMul,  1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
			 0.5f * projMul,  0.5f * projMul, -0.5f * projMul,  1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
			 0.5f * projMul, -0.5f * projMul, -0.5f * projMul,  0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
			 0.5f * projMul, -0.5f * projMul,  0.5f * projMul,  0.0f, 0.0f,  1.0f,  0.0f,  0.0f,

			-0.5f * projMul, -0.5f * projMul, -0.5f * projMul,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f,
			 0.5f * projMul, -0.5f * projMul, -0.5f * projMul,  1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
			 0.5f * projMul, -0.5f * projMul,  0.5f * projMul,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
			-0.5f * projMul, -0.5f * projMul,  0.5f * projMul,  0.0f, 0.0f,  0.0f, -1.0f,  0.0f,

			-0.5f * projMul,  0.5f * projMul, -0.5f * projMul,  0.0f, 1.0f,  0.0f,  1.0f,  0.0f,
			 0.5f * projMul,  0.5f * projMul, -0.5f * projMul,  1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
			 0.5f * projMul,  0.5f * projMul,  0.5f * projMul,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
			-0.5f * projMul,  0.5f * projMul,  0.5f * projMul,  0.0f, 0.0f,  0.0f,  1.0f,  0.0f
		};

		data[0]->indices = new unsigned int[36]
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

		data[0]->dataSize = 192;
		data[0]->indicesSize = 36;

		break;
	}
	default:
		break;
	}
}

Mesh::Mesh(bool _isPerspective, const std::string & path)
{
	loadMesh(_isPerspective, path);
}

Mesh::~Mesh()
{
	for (unsigned int i = 0; i < data.size(); i++)
	{
		delete[] data[i]->data;
		delete[] data[i]->indices;
		delete data[i];
	}
}
