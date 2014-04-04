#include "Platform/SpriteSheetObject.h"
#include "Platform/debug.h"
#include "Platform/Graphics.h"
#include <vector>
#include <incl/glm/gtc/type_ptr.hpp>
#include "Platform/New.h"
#include "Platform/Leak.h"

SpriteSheetObject::SpriteSheetObject(int frameWidth, int frameHeight, int frameSpeed, int frames, Texture* texture, Shader* shader, std::string n):
	_shader(shader),
	_texture(texture),
	_name(n)
{
	_frames   = frames;
	_curFrame = 0;
	 time     = 0;

	setAnimation(0, frames, frameSpeed);
	init(frameWidth, frameHeight, frames, glm::vec4(1.f,1.f,1.f,1.f));

}

SpriteSheetObject::~SpriteSheetObject(void)
{
	delete _texture;
	delete _vertexData;
	delete _indexData;
}

void SpriteSheetObject::init(int frameWidth, int frameHeight, int frames, glm::vec4 color)
{
	setPosition(glm::vec3(0,0,0));

	std::vector<GLfloat> data(32);

	data[0] = -frameWidth / 2.0f;	data[1] =  -frameHeight / 2.0f;
	data[8] = -frameWidth / 2.0f;	data[9] =   frameHeight / 2.0f;

	data[16] = frameWidth / 2.0f;	data[17] = -frameHeight / 2.0f;
	data[24] = frameWidth / 2.0f;	data[25] =  frameHeight / 2.0f;


	for(int i = 2; i< 32; i+= 8)
	{
		data[i+0] =	color.x;
		data[i+1] = color.y;
		data[i+2] = color.z;
		data[i+3] = 1.0f;
	}

	data[6]  = 0.0f;	data[7]  = 1.0f;
	data[14] = 0.0f;	data[15] = 0.0f;
	data[22] = 1.0f/frames;	data[23] = 1.0f;
	data[30] = 1.0f/frames;	data[31] = 0.0f;
	
	_vertexData = EVO_NEW VertexData(data);
	
	const GLushort iData[] = { 0, 1, 2, 2, 1, 3 };
	std::vector<GLushort> indexData(iData, iData+6);

	_indexData = EVO_NEW IndexData(indexData);
}

void SpriteSheetObject::setColor(glm::vec4 color)
{
	GLfloat colors[] = {color.x, color.y, color.z, color.w};
	for(int i = 2; i <32; i += 8)
	{
		_vertexData->setData(GL_ARRAY_BUFFER, sizeof(GLfloat)*i, sizeof(GLfloat)*4, colors);
	}
}

void SpriteSheetObject::draw(glm::mat4 &projectionMatrix)
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

void SpriteSheetObject::update(float dt)
{
	float frameWidth = 1.0f/_frames;
	float texPos = frameWidth*_curFrame;

	GLfloat textureCoords[] = {texPos,texPos,texPos+frameWidth,texPos+frameWidth};

	if(_speed < time)
	{
		_vertexData->setData(GL_ARRAY_BUFFER, sizeof(GLfloat)*6,  sizeof(GLfloat), (void*)&textureCoords[0]);
		_vertexData->setData(GL_ARRAY_BUFFER, sizeof(GLfloat)*14, sizeof(GLfloat), (void*)&textureCoords[1]);
		_vertexData->setData(GL_ARRAY_BUFFER, sizeof(GLfloat)*22, sizeof(GLfloat), (void*)&textureCoords[2]);
		_vertexData->setData(GL_ARRAY_BUFFER, sizeof(GLfloat)*30, sizeof(GLfloat), (void*)&textureCoords[3]);

		time = 0;
		_curFrame++;
	}

	time++;

	if(_curFrame > _endFrame)
		_curFrame = _startFrame;

}

void SpriteSheetObject::setSpeed(float speed)
{
	_speed = speed;
}

float SpriteSheetObject::getSpeed()
{
	return _speed;
}

void SpriteSheetObject::setAnimation(int startFrame, int endFrame, int speed)
{
	_startFrame = startFrame;
	_curFrame = startFrame;
	_endFrame = endFrame;
	_speed = speed;
}