#ifndef VIEWPORT_H_
#define VIEWPORT_H_

#include <iostream>
#include <Platform/OpenGL.hpp>
#include <stdlib.h>
#include <incl/glm/glm.hpp>
#include "Platform/Object.h"
#include "Platform/Camera.h"

class Viewport
{
public:

	Viewport(float width,float height);
	~Viewport();
	glm::mat4 projectionMatrix;
	void draw(Object* object);
	glm::mat4 viewMatrix;
	static Camera* camera;
	glm::vec3 movement;
	void moveCamera(float X, float Y);

private:
	float width, height;
};
#endif