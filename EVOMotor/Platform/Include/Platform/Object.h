#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <incl/glm/glm.hpp>
#include <incl/glm/gtx/transform.hpp>
#include "incl/glm/matrix.hpp"

enum OBJECT_TYPE
{
	UNDEFINED,
	SPRITE,
	SPRITESHEET,
	TEXT
};

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
	void setPosition(const float x, const float y);
	void setLayer(const int layer);
	void setScale(const glm::vec3& scale);
	void setScale(const float scale);
	void setRotationX(float rotation);
	void setRotationY(float rotation);
	void setRotationZ(float rotation);
	void setProjectionMatrix(glm::mat4& matrix);

	float getRotation() const;
	float getWidth();
	float getHeight();
	glm::vec3& getScale();
	glm::vec3& getPosition();
	glm::mat4& getMatrix();

	std::string _name;

	int _type;
	int _layer;

protected:

	void calculateMatrix();

	float _rotation;
	bool _recalculateMatrix;

	glm::vec3 _position;
	glm::vec3 _scale;

	glm::mat4 _translationMatrix;
	glm::mat4 _rotationMatrix;
	glm::mat4 _scaleMatrix;
	glm::mat4 _combinedMatrix;
	glm::mat4 _projectionMatrix;
};

#endif