/*Viewport.h
* Sets projection matrives and handles
* the camera & viewport.
*/
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

	//Moves the camera for the amount of X and Y
	void moveCamera(float X, float Y);

	//Checks the current window size and sets it to projection matrix
	//and sends the projection matrix to the object class to use.
	void draw(Object* object);

	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	static Camera* camera;
	glm::vec3 movement;

private:
	float width, height;
};
#endif