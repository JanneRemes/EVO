#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include <iostream>
#include <Platform/OpenGL.hpp>
#include <string>
#include <stdlib.h>
#include <incl/glm/glm.hpp>
#include "Platform/Object.h"

class Rectangle : public Object
{
public:
	Rectangle(float width, float height, glm::vec2 position);
	~Rectangle();

	glm::vec2 m_dimensions;

	void init();
	void update(float dt);
	void draw(glm::mat4 &projectionMatrix);
	bool checkCol(const Rectangle&) const;

private:



};


#endif