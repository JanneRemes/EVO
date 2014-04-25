#include "Platform/Rectangle.h"
#include "Platform/debug.h"
#include "Platform/New.h"
#include "Platform/Leak.h"


Rect::Rect(){}

Rect::Rect(float width, float height, glm::vec2 position)
{
	m_dimensions = glm::vec2(width,height);
	setPosition(position);
}
Rect::~Rect()
{

}
void Rect::init()
{

}
void Rect::update(float dt)
{

}
void Rect::draw(glm::mat4 &projectionMatrix)
{

}
bool Rect::checkCol(const Rect& rec) const
{
	//wtf is this, fix it later
	/*return _position.x+m_dimensions.x/2 < rec._position.x-rec.m_dimensions.x/2 ||
		_position.x-m_dimensions.x/2 > rec._position.x+rec.m_dimensions.x/2 ||
		_position.y-m_dimensions.y/2 > rec._position.y+rec.m_dimensions.y/2 ||
		_position.y+m_dimensions.y/2 < rec._position.y-rec.m_dimensions.y/2;*/


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

