/*VertexData.h
*
*
*/
#ifndef VERTEXDATA_H_
#define VERTEXDATA_H_

#include <vector>

#include <iostream>
#include <Platform/OpenGL.hpp>
#include <stdlib.h>
#include "Platform/Shader.h"

class VertexData
{
public:

	VertexData(std::vector<GLfloat> &data);
	/*
	VertexData(std::vector<glm::vec3> &data);
	VertexData(std::vector<glm::vec2> &data);
	*/
	~VertexData();

//Binds a named buffer to a target
	void bindBuffers();
//Defines an array of generic vertex attribute data
//and enables a generic vertex attribute array
	void setAttribute(int location,int components,int stride, int offset);
//Updates a subset of a buffer object's data store and unbinds buffer
	void setData(int target, unsigned int offset, unsigned int size, void* data);
//Gets data what is set to _data
	std::vector<GLfloat>& getData();

private:

	void init();

	GLuint _vertexBufferObject;
	std::vector<GLfloat> _data;

};

#endif