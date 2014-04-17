#ifndef CAMERA_H_
#define CAMERA_H_

#include <incl/glm/glm.hpp>
#include <incl/glm/gtx/transform.hpp>
#include "incl/glm/matrix.hpp"
#include "Platform/Object.h"


class Camera : public Object
{
public:
	Camera();//Konstruktori
	~Camera();//Destruktori

	void update(float dt){} //Tyhj� update
	void draw(glm::mat4 &projectionMatrix){} //Tyhj� piirtofunktio, parametrin� projektiomatriisi
};


#endif