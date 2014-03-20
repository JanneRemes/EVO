#include "Platform/Object.h"
#include "Platform/Graphics.h"

Object::Object():
	_position(glm::vec3::_null), //= position = (glm::vec3::_null)
	_rotation(0),				// = rotation = 0
	_scale(glm::vec3(1,1,1)), // = scale = (glm::vec3(1,1,1))
	_recalculateMatrix(true) // = recalculateMatrix = true
{
	setScale(_scale);
}

Object::~Object() {}

void Object::setPosition(const glm::vec3& position)
{
	_position = position;
	_translationMatrix = glm::translate(_position);
	_recalculateMatrix = true;
}

void Object::setPosition(const float x, const float y, const float z)
{
	setPosition(glm::vec3(x,y,z));
}

void Object::setPosition(const float x, const float y)
{
	setPosition(glm::vec3(x,y,_position.z));
}

void Object::setPosition(const glm::vec2& position)
{
	setPosition(glm::vec3(position.x, position.y, _position.z));
}

void Object::setScale(const glm::vec3& scale)
{
	_scale = scale;
	_scaleMatrix = glm::scale(_scale);
	_recalculateMatrix = true;
}

void Object::setScale(const float scale)
{
	setScale(glm::vec3(scale, scale, scale));
}

void Object::setRotationX(float rotation)
{
	_rotation = rotation;
	_rotationMatrix = glm::rotate(_rotation,glm::vec3(1.f,0.f,0.f));
	_recalculateMatrix = true;
}

void Object::setRotationY(float rotation)
{
	_rotation = rotation;
	_rotationMatrix = glm::rotate(_rotation,glm::vec3(0.f,1.f,0.f));
	_recalculateMatrix = true;
}

void Object::setRotationZ(float rotation)
{
	_rotation = rotation;
	_rotationMatrix = glm::rotate(_rotation,glm::vec3(0.f,0.f,1.f));
	_recalculateMatrix = true;
}

void Object::setProjectionMatrix(glm::mat4& matrix)
{
	_projectionMatrix = matrix;
}

float Object::getRotation() const
{
	return _rotation;
}

glm::vec3& Object::getScale()
{
	return _scale;
}

glm::vec3& Object::getPosition()
{
	return _position;
}

glm::mat4& Object::getMatrix()
{
	if(_recalculateMatrix)
	{
		calculateMatrix();
		_recalculateMatrix = false;
	}
	return _combinedMatrix;
}

void Object::calculateMatrix()
{
	_combinedMatrix = _translationMatrix * _rotationMatrix * _scaleMatrix;
}