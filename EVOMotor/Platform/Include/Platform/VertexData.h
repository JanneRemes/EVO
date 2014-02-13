#ifndef VERTEXDATA_H_
#define VERTEXDATA_H_

#include <vector>
#include "Platform/Window.h"
#include "Platform/Shader.h"

class VertexData
{
public:

	VertexData(std::vector<GLfloat> &data);/*
	VertexData(std::vector<glm::vec3> &data);
	VertexData(std::vector<glm::vec2> &data);*/
	~VertexData();

	void bindBuffers();
	void setAttribute(int location,int components,int stride, int offset);
	void setData(int target, unsigned int offset, unsigned int size, void* data);
	std::vector<GLfloat>& getData();

private:

	void init();

	GLuint _vertexBufferObject;
	std::vector<GLfloat> _data;
	//


};

#endif