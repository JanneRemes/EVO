#include "Platform/Texture.h"
#include <time.h>
#include "Platform/debug.h"
#include "Platform/New.h"
#include "Platform/Leak.h"

Texture::Texture()
{
}

Texture::Texture(GLubyte* data,int width,int height,int depth):
_data(data),
_width(width),
_height(height),
_depth(depth)
{
	init();
}
Texture::Texture(GLubyte* data):
_data(data),
_width(10),
_height(10)
{
	init();
}

Texture::~Texture(void)
{

}

void Texture::init()
{
	int format = _depth == 24 ? GL_RGB : GL_RGBA;

	glGenTextures(1, &_textureID);
	
	glBindTexture(GL_TEXTURE_2D, _textureID);

	glTexImage2D(GL_TEXTURE_2D,0 , format, _width, _height,0,format,GL_UNSIGNED_BYTE,_data);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind(Shader* shader)
{
	glActiveTexture(GL_TEXTURE0);
	checkGLError("glActiveTexture");

	glBindTexture(GL_TEXTURE_2D, _textureID);
	checkGLError("glBindTextures");

	shader->setUniform("vSampler", 0);
}

GLuint Texture::getTextureObject() const
{
	return _textureID;
}

Texture* Texture::generateRandom(glm::vec2& size)
{
	const int length = size.x * size.y * 4;
	GLubyte* pixelData = EVO_NEW GLubyte[length];
	for(int i = 0; i < length; i++)
	{
		pixelData[i] = rand() % 255;
	}
	return EVO_NEW Texture(pixelData, (int)size.x, (int)size.y, 24);
}

Texture* Texture::load(const std::string &fileName)
{
	tgaHeader header;
	GLubyte* data = FileReader::loadTGA(fileName, header);
	return EVO_NEW Texture(data, header.width, header.height, header.depth);

	//writeLog("\ntexturesize: %d\n",sizeof(*data)); //Prints size of texture to debugger
}

