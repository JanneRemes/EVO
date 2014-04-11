#include "Platform/SpriteObject.h"
#include "Platform/debug.h"
#include "Platform/Graphics.h"
#include <vector>
#include <incl/glm/gtc/type_ptr.hpp>
#include "Platform/New.h"
#include "Platform/Leak.h"

SpriteObject::SpriteObject(int x,int y,int width,int height,Texture* texture, Shader* shader, std::string n):
	_shader(shader),
	_texture(texture),
	_name(n),
	_rectangle(width,height,glm::vec2(x,y))
{
	init(x,y,width,height,glm::vec4(1.f,1.f,1.f,1.f));
}

SpriteObject::~SpriteObject(void)
{
	delete _texture;
	delete _vertexData;
	delete _indexData;
}

void SpriteObject::init(int x,int y,int width, int height,glm::vec4 color)
{
	setPosition(glm::vec3(x, y, 0));

	std::vector<GLfloat> data(32);

	data[0] = -width / 2.0f;	data[1] =  -height / 2.0f;
	data[8] = -width / 2.0f;	data[9] =   height / 2.0f;

	data[16] = width / 2.0f;	data[17] = -height / 2.0f;
	data[24] = width / 2.0f;	data[25] =  height / 2.0f;

	for(int i = 2; i< 32; i+= 8)
	{
		data[i+0] =	color.x;
		data[i+1] = color.y;
		data[i+2] = color.z;
		data[i+3] = 1.0f;
	}

	data[6]  = 0.0f;	data[7]  = 1.0f;
	data[14] = 0.0f;	data[15] = 0.0f;
	data[22] = 1.0f;	data[23] = 1.0f;
	data[30] = 1.0f;	data[31] = 0.0f;
	
	_vertexData = EVO_NEW VertexData(data);

	const GLushort iData[] = { 0, 1, 2, 2, 1, 3 };
	std::vector<GLushort> indexData(iData, iData+6);

	_indexData = EVO_NEW IndexData(indexData);
}

void SpriteObject::setColor(glm::vec4 color)
{
	GLfloat colors[] = {color.x, color.y, color.z, color.w};
	for(int i = 2; i <32; i += 8)
	{
		_vertexData->setData(GL_ARRAY_BUFFER, sizeof(GLfloat)*i, sizeof(GLfloat)*4, colors);
	}
}

const Rectangle& SpriteObject::getRectangle()
{
	return _rectangle;
}

void SpriteObject::draw(glm::mat4 &projectionMatrix)
{
	glUseProgram(_shader->program());

	if (_texture)
		_texture->bind(_shader);
	glm::mat4 model = getMatrix();
	glm::vec4 gl_Position = projectionMatrix * model * glm::vec4(100,100, 0, 1.0);

	_shader->setUniform("projection", glm::value_ptr(projectionMatrix)); 
	_shader->setUniform("model", glm::value_ptr(getMatrix()));

	static const int stride = sizeof(GLfloat)*8;

	_vertexData->bindBuffers();
	_indexData->bindBuffers();

	_vertexData->setAttribute(glGetAttribLocation(_shader->program(), "position"), 2, stride, 0); //vertex positions
	_vertexData->setAttribute(glGetAttribLocation(_shader->program(), "color"), 4, stride, sizeof(GLfloat)*2); //color
	_vertexData->setAttribute(glGetAttribLocation(_shader->program(), "texCoords"), 2, stride, sizeof(GLfloat)*6); //texture coordinates

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
	//glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	checkGLError("glDrawElements");
}

void SpriteObject::update(float dt)
{
	_rectangle.setPosition(_position);
}