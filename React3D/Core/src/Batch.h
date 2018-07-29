#pragma once
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "glm/glm.hpp"

class Batch sealed
{
private:
	unsigned int maxNumVertices;
	unsigned int numUsedVertices;
	VertexArray vertexArrayObject;
	VertexBuffer vertexBufferObject;
	BatchConfig config;
	GuiVertex lastVertex;
	
public:
	Batch(unsigned int _maxNumVertices);
	~Batch();
	bool isBatchConfig(const BatchConfig& config) const;
	bool isEmpty() const;
	bool isEnoughRoom(unsigned _numVertices) const;
	Batch* getFullest(Batch* _batch);
	int getPriority() const;

	void add(const std::vector<int>& _vertices, const BatchConfig& config);

};

struct BatchConfig
{
	unsigned int renderType;
	int priority;
	unsigned int textureId;
	glm::mat4 transformMatrix;
	BatchConfig(unsigned int _renderType, int _priority, unsigned int _textureId) :
		renderType(_renderType), priority(_priority), textureId(_textureId) { }
	bool operator==(const BatchConfig& _other) const
	{
		if (renderType != _other.renderType ||
			priority != _other.priority ||
			textureId != _other.textureId ||
			transformMatrix != _other.transformMatrix)
		{
			return false;
		}
		else
			return true;
	}
	bool operator!=(const BatchConfig& _other) const
	{
		return !(*this == _other);
	}
};

struct GuiVertex
{
	glm::vec2 position;
	glm::vec4 color;
	glm::vec2 texture;
	GuiVertex(glm::vec2 _position, glm::vec4 _color, glm::vec2 _texture = glm::vec2()) :
		position(_position),
		color(_color),
		texture(_texture) { }
};