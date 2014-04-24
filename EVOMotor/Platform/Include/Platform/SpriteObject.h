#ifndef SPRITEOBJECT_H_
#define SPRITEOBJECT_H_

#include <iostream>
#include <Platform/OpenGL.hpp>
#include <stdlib.h>
#include <incl/glm/glm.hpp>
#include <Platform/Shader.h>
#include <Platform/Texture.h>
#include <Platform/VertexData.h>
#include <Platform/IndexData.h>
#include <Platform/Object.h>
#include <Platform/Rectangle.h>

class SpriteObject : public Object
{
public:
	~SpriteObject(void);
	SpriteObject(int x,int y,int width ,int height, Texture* texture, Shader *shader, std::string name);

	void setVertexData(VertexData* vertexData);
	void setColor(glm::vec4 color);
	const Rectangle& getRectangle();

	virtual void draw(glm::mat4 &projectionMatrix);
	virtual void update(float dt);

private:

	void init(int x,int y,int width,int height,glm::vec4 color);

	VertexData* _vertexData;
	IndexData* _indexData;
	Shader* _shader;
	Texture* _texture;
	Rectangle _rectangle;
	

	
};
#endif