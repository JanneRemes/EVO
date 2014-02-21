#include "Platform/IndexData.h"
#include "Platform/debug.h"

//konstruktori
IndexData::IndexData(std::vector<GLushort> &data):
	_data(data)
{
	init();
}

//destruktori
IndexData::~IndexData()
{
}

void IndexData::bindBuffers()
{
	//bind a named buffer object
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
	checkGLError("Bind index buffer");
}


std::vector<GLushort>& IndexData::getData()
{
	return  _data;
}

void IndexData::init()
{
//const GLubyte indexdata[] = {0, 1, 2, 2, 1, 3};
	//_data.shrink_to_fit();

	//generate buffer object names
	glGenBuffers(1, &_indexBuffer);
	checkGLError("glGenBuffers");

	//bind a named buffer object
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
	checkGLError("glBindBuffer");

	//creates and initializes a buffer object's data store
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _data.size()*sizeof(GLushort), &_data[0], GL_STATIC_DRAW);
	checkGLError("glBufferData");
}