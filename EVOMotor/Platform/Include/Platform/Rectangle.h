#ifndef Rect_H_
#define Rect_H_

#include <iostream>
#include <Platform/OpenGL.hpp>
#include <string>
#include <stdlib.h>
#include <incl/glm/glm.hpp>
#include "Platform/Object.h"

class Rect : public Object
{
public:
	Rect();
	Rect(float width, float height, glm::vec2 position);
	~Rect();

	glm::vec2 m_dimensions;

	void init();
	void update(float dt);
	void draw(glm::mat4 &projectionMatrix);
	bool checkCol(const Rect&) const;

private:



};


#endif