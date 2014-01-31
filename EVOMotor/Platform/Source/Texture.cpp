#include "Platform/Texture.h"
#include <time.h>

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

GLubyte* Texture::loadTGA(const std::string& fileName, tgaHeader &header)
{
	std::ifstream file;
	file.open(fileName, std::ios::binary);

	file.read((char*)&header.idLength,1);
	file.read((char*)&header.colorMapType,1);
	file.read((char*)&header.type,1);
	file.seekg(9,std::ios_base::cur);
	file.read((char*)&header.width,2);
	file.read((char*)&header.height,2);
	file.read((char*)&header.depth,1);
	file.read((char*)&header.descriptor,1);
	file.seekg(header.idLength,std::ios_base::cur);

	//24bit / 8 = 3 (RGB), 32bit / 8 = 4 (RGBA)
	int componentCount = header.depth/8;

	int size = componentCount * header.width * header.height;
	GLubyte* data = new GLubyte[size];

	file.read((char*)data,size);

	//data is now BGRA for some reason so we format it to RGBA
	for(int i = 0;i < size; i+= componentCount)
	{
		GLubyte temp = data[i];

		//Switch red and blue
		data[i] = data[i+2];
		data[i+2] = temp;
	}

	file.close();

	return data;
}

GLuint Texture::getTextureObject() const
{
	return _textureID;
}


Texture* Texture::generateRandom(glm::vec2& size)
{
	const int length = size.x * size.y * 4;
	GLubyte* pixelData = new GLubyte[length];
	for(int i = 0; i < length; i++)
	{
		pixelData[i] = rand() % 255;
	}
	return new Texture(pixelData, (int)size.x, (int)size.y, 24);
}