#ifndef VIEWPORT_H_
#define VIEWPORT_H_


#include <iostream>
#include <Platform/OpenGL.hpp>
#include <stdlib.h>
#include <incl/glm/glm.hpp>
#include "Platform/Object.h"


class Viewport
{
public:

	Viewport(float width,float height);
	~Viewport();
	glm::mat4 projectionMatrix;
	void draw(Object* object);

};

#endif