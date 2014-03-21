#ifndef OBJECT_H
#define OBJECT_H

#include <incl/glm/glm.hpp>
#include <incl/glm/gtx/transform.hpp>
#include "incl/glm/matrix.hpp"

class Object
{
	//asetetaan arvoja ja positioneita hyvin paljon
public:
	Object();
	virtual ~Object();

	virtual void update(float dt) = 0;
	virtual void draw(glm::mat4 &projectionMatrix) = 0;

	void setPosition(const glm::vec3& position);
	void setPosition(const glm::vec2& position);
	void setPosition(const float x, const float y, const float z);
	void setPosition(const float x, const float y);
	void setScale(const glm::vec3& scale);
	void setScale(const float scale);
	void setRotationX(float rotation);
	void setRotationY(float rotation);
	void setRotationZ(float rotation);
	void setProjectionMatrix(glm::mat4& matrix);

	float getRotation() const;
	glm::vec3& getScale();
	glm::vec3& getPosition();
	glm::mat4& getMatrix();
	float getWidth();
	float getHeight();


protected:

	void calculateMatrix();

	glm::vec3 _position;
	float _rotation;
	glm::vec3 _scale;
	bool _recalculateMatrix;

	glm::mat4 _translationMatrix;
	glm::mat4 _rotationMatrix;
	glm::mat4 _scaleMatrix;
	glm::mat4 _combinedMatrix;
	glm::mat4 _projectionMatrix;
};

#endif