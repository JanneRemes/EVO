#include "Platform/Viewport.h"
#include "Platform/Window.h"

Viewport::Viewport(float width,float height)
{

	//projectionMatrix = glm::ortho(0.f,width,0.f,height, 0.1f, 100.f);
	
}

Viewport::~Viewport()
{

}

void Viewport::draw(Object* object)
{
	float width = Window::winWidth;
	float height = Window::winHeight;
	projectionMatrix = glm::ortho(0.f,width,0.f,height, 0.1f, 100.f);
	object->draw(projectionMatrix);
}