#ifndef SPRITESHEETOBJECT_H_
#define SPRITESHEETOBJECT_H_

#include <iostream>
#include <Platform/OpenGL.hpp>
#include <stdlib.h>
#include <incl/glm/glm.hpp>
#include "Platform/Shader.h"
#include "Platform/Texture.h"
#include "Platform/VertexData.h"
#include "Platform/IndexData.h"
#include "Platform/Object.h"
#include "Platform/Rectangle.h"

class SpriteSheetObject : public Object
{
public:
	~SpriteSheetObject(void);
	SpriteSheetObject(int frameWidth ,int frameHeight,int frameSpeed,int frames, Texture* texture, Shader *shader, std::string name);

	void setVertexData(VertexData* vertexData);
	void setColor(glm::vec4 color);
//Set and get animation speed
	void setSpeed(float speed);
	float getSpeed(); 
//Set new Animation
	void setAnimation(int startFrame, int endFrame, int speed);

	virtual void draw(glm::mat4 &projectionMatrix);
	virtual void update(float dt);

	const Rect& getRectangle();

	int _frames, _curFrame, _speed, time, _startFrame, _endFrame;
private:
	
	void init(int frameWidth,int frameHeight,int frames,glm::vec4 color);
	
	VertexData* _vertexData;
	IndexData* _indexData;
	Shader* _shader;
	Texture* _texture;
	Rect _rectangle;

};

#endif