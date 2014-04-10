#include "Platform/Rectangle.h"
#include "Platform/debug.h"
#include "Platform/New.h"
#include "Platform/Leak.h"


Rectangle::Rectangle(float width, float height, glm::vec2 position)
{
	m_dimensions = glm::vec2(width,height);
	setPosition(position);
}
Rectangle::~Rectangle()
{

}
void Rectangle::init()
{

}
void Rectangle::update(float dt)
{

}
void Rectangle::draw(glm::mat4 &projectionMatrix)
{

}
bool Rectangle::checkCol(const Rectangle& rec) const
{
	if(_position.x+m_dimensions.x/2 < rec._position.x-rec.m_dimensions.x/2)
		return false;
	else if(_position.x-m_dimensions.x/2 > rec._position.x+rec.m_dimensions.x/2)
		return false;
	else if(_position.y-m_dimensions.y/2 > rec._position.y+rec.m_dimensions.y/2)
		return false;
	else if(_position.y+m_dimensions.y/2 < rec._position.y-rec.m_dimensions.y/2)
		return false;

	return true;
}

