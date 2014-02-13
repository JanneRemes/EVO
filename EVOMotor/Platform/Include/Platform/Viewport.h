#ifndef VIEWPORT_H_
#define VIEWPORT_H_

#include "Platform/Window.h"
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