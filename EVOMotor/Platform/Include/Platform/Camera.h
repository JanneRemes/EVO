#ifndef CAMERA_H_
#define CAMERA_H_

#include <incl/glm/glm.hpp>
#include <incl/glm/gtx/transform.hpp>
#include "incl/glm/matrix.hpp"
#include "Platform/Object.h"


class Camera : public Object
{
public:
	Camera();
	~Camera();

	void update(float dt){}
	void draw(glm::mat4 &projectionMatrix){}
};


#endif